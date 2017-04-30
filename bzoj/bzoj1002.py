n=int(input())
F=[0 for x in range(0, 1000)]
F[1]=1
F[2]=5
for i in range(3,n+1):
	F[i]=3*F[i-1]-F[i-2]+2
print(F[n])
