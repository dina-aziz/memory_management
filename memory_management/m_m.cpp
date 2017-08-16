#include<iostream>
using namespace std;

const int Mem_Limit=1000;
const int Desc_Limit=101;  
enum mem_man{ FF,BF,WF};
struct desc
{
	int base_address;
	int limit;
	int pid;
};
class Memory_Management
{
private :
	bool filled;
	mem_man man_alg;
	desc descriptors[Desc_Limit];
	desc descriptor_table[Desc_Limit-1];
	int memory[Mem_Limit];
	int index;
public :
	Memory_Management();
	void Allocate();
	void Deallocate(int);
	void Sort_Desc();
	int Read(int,int);
	bool Write(int,int,int);
};
Memory_Management::Memory_Management()
{
	index=0;
	filled=false;
	int choice;
	for(int j=0;j<100;j++)
	{
		descriptors[j].base_address=-1;
		descriptors[j].limit=-1;
		descriptors[j].pid=-1;
		descriptor_table[j]=descriptors[j];
	}
	cout<<"\n   Choose the memory management algorithm : ";
	cout<<"\n   Choose : 1 for first fit algorithm .";
	cout<<"\n   Choose : 2 for best fit algorithm .";
	cout<<"\n   Choose : 3 for worst fit algorithm ."<<endl;
	cout<<"\n   Choice : ";
	cin>>choice;
	if(choice== 1) man_alg=FF;
	if(choice== 2) man_alg=BF;
	if(choice== 3) man_alg=WF;
}
void Memory_Management::Sort_Desc()
{
	desc temp;
	for(int j=0;j<Desc_Limit;j++)
		for(int k=j+1;k<Desc_Limit-1;k++)
			if(descriptors[k].base_address<descriptors[j].base_address)
			{
				temp=descriptors[j];
				descriptors[j]=descriptors[k];
				descriptors[k]=temp;
			}
}
void Memory_Management::Allocate()
{
	static int base=-1;
	int space;
	int pid;
	cout<<"\nenter the process pid :";
	cin >>pid;
	cout<<"\nenter the desired allcation space  :";
	cin >>space;
	Sort_Desc();
	if(man_alg==FF)
	{
		int lim;
		int add;
		int last_add_used;
		for(int j=0;j<Desc_Limit-1;j++)
		{
			if(!filled)
			{
				last_add_used=descriptors[j].base_address;
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[j].base_address==-1)
					{
						descriptors[j].base_address=base+1;
						descriptors[j].limit=space;
						descriptors[j].pid=pid;
						descriptor_table[index++]=descriptors[j];
						if(j==99) filled=1;
						break;
					}
				}
			}
			else
			{
			    if( descriptors[0].base_address>=space)
				{
					for(int m=Desc_Limit-1;m>=0;m--)
						descriptors[m]=descriptors[m+1];
					descriptors[0].base_address=0;
					descriptors[0].limit=space;	
					descriptors[0].pid=pid;
					descriptor_table[index++]=descriptors[0];
					break;
				}
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[k].base_address!=-1 )
					{
							if((descriptors[k+1].base_address-(descriptors[k].base_address+descriptors[k].limit))>=space)
							{
								descriptors[Desc_Limit-1].base_address=descriptors[k].base_address+descriptors[k].limit+1;  
								descriptors[Desc_Limit-1].limit=space;
								descriptors[Desc_Limit-1].pid=pid;
								descriptor_table[index++]=descriptors[Desc_Limit-1];
								Sort_Desc();
								break;
							}
					}
				}
			}
		}
	}
	else if(man_alg==BF)
	{
		int least_space=100;
		int least_space_add=0;
		int lim;
		int add;
		int last_add_used;
		for(int j=0;j<Desc_Limit-1;j++)
		{
			if(!filled)
			{
				last_add_used=descriptors[j].base_address;
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[j].base_address==-1)
					{
						descriptors[j].base_address=base+1;
						descriptors[j].limit=space;
						descriptors[j].pid=pid;
						descriptor_table[index++]=descriptors[j];
						if(j==99) filled=1;
						break;
					}
				}
			}
			else
			{
			    if( int s=descriptors[0].base_address>=space)
				{
					if(s<least_space)
					{
						least_space=s;
						least_space_add=0;
					}
					break;
				}
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[k].base_address!=-1 )
					{
							if(int s=(descriptors[k+1].base_address-(descriptors[k].base_address+descriptors[k].limit))>=space)
							{
								if(s<least_space)
								{
									least_space=s;
									least_space_add=0;
								}
								break;
							}
					}
				}
			}
		}
		descriptors[Desc_Limit-1].base_address=least_space_add;
		descriptors[Desc_Limit-1].limit=space;
	    descriptors[Desc_Limit-1].pid=pid;
		descriptor_table[index++]=descriptors[Desc_Limit-1];
		Sort_Desc();
	}
	else if(man_alg==WF)
	{
		int least_space=0;
		int least_space_add;
		int lim;
		int add;
		int last_add_used;
		for(int j=0;j<Desc_Limit-1;j++)
		{
			if(!filled)
			{
				last_add_used=descriptors[j].base_address;
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[j].base_address==-1)
					{
						descriptors[j].base_address=base+1;
						descriptors[j].limit=space;
						descriptors[j].pid=pid;
						if(j==99) filled=1;
						break;
					}
				}
			}
			else
			{
			    if( int s=descriptors[0].base_address>=space)
				{
					if(s>least_space)
					{
						least_space=s;
						least_space_add=0;
					}
					break;
				}
				for(int k=0;k<Desc_Limit-1;k++)
				{
					if(descriptors[k].base_address!=-1 )
					{
							if(int s=(descriptors[k+1].base_address-(descriptors[k].base_address+descriptors[k].limit))>=space)
							{
								if(s>least_space)
								{
									least_space=s;
									least_space_add=0;
								}
								break;
							}
					}
				}
			}
		}
		descriptors[Desc_Limit-1].base_address=least_space_add;
		descriptors[Desc_Limit-1].limit=space;
	    	descriptors[Desc_Limit-1].pid=pid;
		descriptor_table[index++]= descriptors[Desc_Limit-1];
		Sort_Desc();
	}
}
int Memory_Management::Read(int p_id,int add)
{
	for(int j=0;j<Desc_Limit-1;j++)
		if(descriptor_table[j].pid==p_id && add>=descriptor_table[j].base_address && add<descriptor_table[j].limit)
			return memory[descriptor_table[j].base_address+add];
	cout<<" \nAddress is out of range.."<<endl;
	return 0;
}
bool Memory_Management::Write(int p_id,int add,int val)
{
	for(int j=0;j<Desc_Limit-1;j++)
		if(descriptor_table[j].pid==p_id && add>=descriptor_table[j].base_address && add<descriptor_table[j].limit)
		{memory[descriptor_table[j].base_address+add]=val;return 1;}
	cout<<" \nAddress is out of range.."<<endl;
	return 0;
}
void Memory_Management::Deallocate(int p_id)
{
	for(int j=0;j<Desc_Limit-1;j++)
		if(descriptor_table[j].pid==p_id)
		{
			descriptor_table[j].pid=-1;
			descriptor_table[j].base_address=-1;
			descriptor_table[j].limit=-1;
			break;
		}
	for(int j=0;j<Desc_Limit-1;j++)
		if(descriptors[j].pid==p_id)
		{
			descriptors[j].pid=-1;
			descriptors[j].base_address=-1;
			descriptors[j].limit=-1;
			break;
		}
		Sort_Desc();
}

int main()
{
	int choice,pid,add,val;
	char again='y';
	Memory_Management m1;
	while(again=='y')
	{
		cout<<" \n\nIf you want to allocate memory to a new process press 1.";
		cout<<" \nIf you want to deallocate memory given to a process press 2.";
		cout<<" \nIf you want to read from memory press 3.";
		cout<<" \nIf you want to write to memory  press 4.";
		cout<<" \nChoice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			m1.Allocate();
			break;
		case 2:
			cout<<" \nenter process pid  :  ";
			cin>>pid;
			m1.Deallocate(pid);
			break;
		case 3:
			cout<<" \nenter process pid  :  ";
			cin>>pid;
			cout<<" \nenter memory address  :  ";
			cin>>add;
			val=m1.Read(pid,add);
			cout<<val<<endl;
			break;
		case 4:
			cout<<" \nenter process pid  :  ";
			cin>>pid;
			cout<<" \nenter memory address  :  ";
			cin>>add;
			cout<<" \nenter value  :  ";
			cin>>val;
			m1.Write(pid,add,val);
			break;
		default:
			cout<<" \nThis choice doesn't exist .. Try again ."<<endl;
			break;
		}
		cout<<" \nDo more tasks ?(y/n) ";
		cin>>again;
	}
		return 0;
}