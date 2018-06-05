void MSDelay(unsigned int);

void MSDelay(unsigned int itime)
{
unsigned int it,jt;
for (it=0;it<itime;it++)
for (jt=0;jt<1275;jt++);
}

