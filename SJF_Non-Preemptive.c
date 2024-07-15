#include<stdio.h>

void main()
{
    int n,c=0;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    int proc_id[n],at[n],bt[n],ct[n],tat[n],wt[n],m[n];
    double avg_tat=0.0,ttat=0.0,avg_wt=0.0,twt=0.0;
    for(int i=0;i<n;i++)
    {    proc_id[i]=i+1;m[i]=0;}
    printf("Enter arrival times:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&at[i]);
    printf("Enter burst times:\n");
    for(int i=0;i<n;i++)
        scanf("%d",&bt[i]);

    //completion time
    int count=0,mb,p=0,min=0;
    while(count<n)
    {
        min=bt[0];mb=0;
        for(int i=0;i<n;i++)
        {
            if(at[i]<=c && m[i]!=1)
            {
                min=bt[i];mb=i;
                for(int k=0;k<n;k++)
                {
                    if(bt[k]<min && at[k]<=c && m[k]!=1)
                    {
                        min=bt[k];mb=k;
                    }
                }
                m[mb]=1;count++;
                if(c>=at[mb])
                    c+=bt[mb];
                else
                    c+=at[mb]-ct[p]+bt[mb];
                ct[mb]=c;
            }
            p=mb;
            if(count==n)
            break;
        }
    }

    /*for(int i=0;i<n;i++)
    {
        if(c>=at[i])
            c+=bt[i];
        else
            c+=at[i]-ct[i-1]+bt[i];
        ct[i]=c;
    }*/

    //turnaround time
    for(int i=0;i<n;i++)
        tat[i]=ct[i]-at[i];
    //waiting time
    for(int i=0;i<n;i++)
        wt[i]=tat[i]-bt[i];

    printf("FCFS scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",proc_id[i],at[i],bt[i],ct[i],tat[i],wt[i]);

    for(int i=0;i<n;i++)
    {
        ttat+=tat[i];twt+=wt[i];
    }
    avg_tat=ttat/(double)n;
    avg_wt=twt/(double)n;
    printf("\nAverage turnaround time:%lfms\n",avg_tat);
    printf("\nAverage waiting time:%lfms\n",avg_wt);
}
