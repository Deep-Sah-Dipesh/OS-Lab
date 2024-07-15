//RRS
#include<stdio.h>

void
sort (int proc_id[], int at[], int bt[], int b[], int n)
{
  int min = at[0], temp = 0;
  for (int i = 0; i < n; i++)
	{
	  min = at[i];
	  for (int j = i; j < n; j++)
		{
		  if (at[j] < min)
			{
			  temp = at[i];
			  at[i] = at[j];
			  at[j] = temp;
			  temp = bt[j];
			  bt[j] = bt[i];
			  bt[i] = temp;
			  temp = b[j];
			  b[j] = b[i];
			  b[i] = temp;
			  temp = proc_id[i];
			  proc_id[i] = proc_id[j];
			  proc_id[j] = temp;
			}
		}
	}
}

void
main ()
{
  int n, c = 0, t = 0;
  printf ("Enter number of processes: ");
  scanf ("%d", &n);
  printf ("Enter Time Quantum: ");
  scanf ("%d", &t);
  int proc_id[n], at[n], bt[n], ct[n], tat[n], wt[n], b[n], rt[n], m[n];
  int f = -1, r = -1;
  int q[100];
  int count = 0;
  double avg_tat = 0.0, ttat = 0.0, avg_wt = 0.0, twt = 0.0;
  for (int i = 0; i < n; i++)
	proc_id[i] = i + 1;
  printf ("Enter arrival times:\n");
  for (int i = 0; i < n; i++)
	scanf ("%d", &at[i]);
  printf ("Enter burst times:\n");
  for (int i = 0; i < n; i++)
	{
	  scanf ("%d", &bt[i]);
	  b[i] = bt[i];
	  m[i] = 0;
	  rt[i] = -1;
	}

  sort (proc_id, at, bt, b, n);

  f = r = 0;
  q[0] = proc_id[0];

  //completion time
  int p = 0, i = 0;
  while (f >= 0)
	{
	  p = q[f++];
	  i = 0;
	  while (p != proc_id[i])
		i++;
	  if (b[i] >= t)
		{
		  if (rt[i] == -1)
			rt[i] = c;
		  b[i] -= t;
		  c += t;
		  m[i] = 1;
		}
	  else
		{
		  if (rt[i] == -1)
			rt[i] = c;
		  c += b[i];
		  b[i] = 0;
		  m[i] = 1;
		}
	  m[0] = 1;
	  for (int j = 0; j < n; j++)
		{
		  if (at[j] <= c && proc_id[j] != p && m[j] != 1)
			{
			  q[++r] = proc_id[j];
			  m[j] = 1;
			}
		}
	  if (b[i] == 0)
		{
		  count++;
		  ct[i] = c;
		}
	  else
		q[++r] = proc_id[i];

	  if (f > r)
		f = -1;
	}


  //turnaround time and RT
  for (int i = 0; i < n; i++)
	{
	  tat[i] = ct[i] - at[i];
	  rt[i] = rt[i] - at[i];
	}
  //waiting time
  for (int i = 0; i < n; i++)
	wt[i] = tat[i] - bt[i];

  printf ("\nRRS scheduling:\n");
  printf ("PID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
  for (int i = 0; i < n; i++)
	printf ("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], at[i], bt[i], ct[i],
			tat[i], wt[i], rt[i]);

  for (int i = 0; i < n; i++)
	{
	  ttat += tat[i];
	  twt += wt[i];
	}
  avg_tat = ttat / (double) n;
  avg_wt = twt / (double) n;
  printf ("\nAverage turnaround time:%lfms\n", avg_tat);
  printf ("\nAverage waiting time:%lfms\n", avg_wt);
}