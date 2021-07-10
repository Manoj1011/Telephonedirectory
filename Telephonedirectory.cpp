#include<stdio.h>
#include<stdlib.h>

struct Numbers                      //Defining structure which contains mobile number and comment 
{                                   
    char mobnum[15];                //Character array which takes mobile number as input
    char comment[50];               //Character array which stores comment related to above mobile number
};
struct directory                    //Defining structure with data type character and integer and contains structure Numbers as a pointer
{
    char Name[50];                  //character array takes name of the input
    int numofnumbers;               //input takes no of numbers user wants to give as an integer
    struct Numbers *numbers;        //A structure pointer point to Number stucture which declared above
};
struct directory_Modify             //Defining structure with data type character and integer and contains structure Numbers
{
    char Name[50];                  //character array takes name of the input
    int numofnumbers;               //input takes no of numbers user wants to give as an integer
    struct Numbers numbers[20];        //A structure array point to Number structure
};
/*Function description : This function takes user inputs and stores it in the form of a structures which we defined above.
Input: Name,number of numbers user want to give,comment,number
Output: Returns a structure with all user input data*/
struct directory readfromuser(char c){  
    struct directory phn;
    printf("Enter name:");
    scanf(" %[^\n]",phn.Name);						// takes the username as the input 
    printf("How many multiple numbers do you want to give:");
    scanf(" %d",&(phn.numofnumbers));					// takes the no of phone numbers from input 
    phn.numbers = (struct Numbers*)calloc(phn.numofnumbers,sizeof(struct Numbers)); //creating structure array using calloc dynamically 											       to store phone numbers and comments wrt to 													each phone number 
    for(int i=0;i<phn.numofnumbers;i++)
    {
        printf("Enter the %d number:",i+1);
        scanf(" %s",phn.numbers[i].mobnum);			// takes the mobile numbers as input
        printf("Enter the comment for the above number:");
        scanf(" %[^\n]",phn.numbers[i].comment);		// takes the comment wrt to each phone number
    }
    return phn;
}
/*Function description : This function append the given data into text file named phn.txt
*/
void writetofile(struct directory phn){
    char k[50]=", This is your Data.";
    FILE *fp= fopen("phone.txt","a");  //this file pointer opens phone.txt file for appending Data
    fprintf(fp,"%s%s\n",phn.Name,k); //this line is to indicate each individual data
    fprintf(fp,"%s\t",phn.Name);     //this line appends the user name into the file
    fprintf(fp,"%d\n",phn.numofnumbers);  //this line appends the no of phone numbers into the file
    for(int i=0;i<phn.numofnumbers;i++){  //this loop is to append each phone number and comment wrt to each Name
        fprintf(fp,"%s\t%s\n",phn.numbers[i].comment,phn.numbers[i].mobnum);
    }
    fclose(fp);  //this line is used to close the opened file
}
/*Function Description: This function reads the data inside the file and returns the structure pointer array
Input: File pointer */
struct directory* readtofile(FILE *fp){
    struct directory *p=(struct directory*) calloc(1,sizeof(struct directory)); //creating a structure pointer array dynamically to store 											  each individual data  
    if (fp==NULL) return NULL;
    fscanf(fp,"%[^\t]%d\n",p->Name,&p->numofnumbers); //this line reads the name and no of phone numbers
    p->numbers=(struct Numbers*)calloc(p->numofnumbers,sizeof(struct Numbers));  // creating structure pointer array using calloc 											    dynamically to store phone numbers and comments wrt to 											    each phone number 
    for(int i=0;i<p->numofnumbers;i++){
        fscanf(fp,"%[^\t]%s\n",p->numbers[i].comment,p->numbers[i].mobnum);  // this line reads the comment and phone number
    }
    return p;
}
/*Function Description: This Function clears the allocated memory*/
void clearmemory(struct directory phn){
    free(phn.numbers);
}
/*Function Description: This Function prints the details of each name if they are present in the file */
void printstruct(struct directory p){
    printf("Given Contact Found.This is the Data with given name:\n");
    printf("--------------------------------------------\n");
    printf("Name    :%s\n",p.Name);
    for(int i=0;i<p.numofnumbers;i++){
        printf("Number %d:%s    %s\n",i+1,p.numbers[i].comment,p.numbers[i].mobnum);
    }
    printf("--------------------------------------------\n");
}
/*Function Description: This Function compares two strings and returns 1 if they are same else 0 */
int compare_str(char a[],char b[]){
    int index=0;
    while(a[index]!='\0' && b[index]!=0){
        if(a[index]!=b[index]) return 0;
        index++;
    }
    if(a[index]=='\0' && b[index]=='\0')  return 1;
    return 0;
}
/*Function Description: This Function reads the file with given name as input and prints the details of the name if it is found
Input:gets string which is name from user and file pointer
Output:prints the data if given name from user is matched */
int search(char temp_str[],FILE *fp){
    struct directory *std=readtofile(fp);
    int strcmp=compare_str(temp_str,std->Name); 
    if (compare_str(temp_str,std->Name)==1) 
    {
        printstruct(*std);		//this line prints the details of given name if "if" condition satisfied
        clearmemory(*std);		//this line clears the allocated memory
        return 1;
    }
    return 0;
}
/*Function Description: This Function is used to modify the name or phone number or comment of each phone number  */
void modify(){
    FILE *fp1=fopen("phone.txt","r"); //this line is to open the file for reading
    char Name_M[50],ss[50],k[50];
    int i=0,x=0,j,struct_count;
    struct directory *dup;
    struct directory_Modify people[50];
    printf("enter the name you want modify:");
    scanf(" %[^\n]",Name_M);	//this line to take name from user which you want to modify the deatils of that name
    while (fscanf(fp1,"%s %[^\n]\n",ss,k)!=EOF)
    {   
        dup=readtofile(fp1); //to read the data from file pointer fp1
        for(j=0;dup->Name[j]!='\0';j++) //this loop is used to store the name of the person in structure directory_Modify people
            people[i].Name[j]=dup->Name[j];
        people[i].Name[j]='\0';			//to indicate end of the string 
        people[i].numofnumbers=dup->numofnumbers;//to store no of phone numbers into people array
        for(int q=0;q<(dup->numofnumbers);q++) //this loop is used to store phone numbers and comments into people array
        {   int count_c=0,count_m=0;
            for(int k=0;dup->numbers[q].comment[k]!='\0';k++) //this loop is used to store comments into people array 
            {
                count_c++;
                people[i].numbers[q].comment[k]=dup->numbers[q].comment[k];
            }
            people[i].numbers[q].comment[count_c]='\0';
            for(int w=0;dup->numbers[q].mobnum[w]!='\0';w++)  //this loop is used to store phone numbers into people array
            {
                count_m++;
                people[i].numbers[q].mobnum[w]=dup->numbers[q].mobnum[w];
            }
            people[i].numbers[q].mobnum[count_m]='\0';
        }
        if (compare_str(people[i].Name,Name_M)==1)  x=i+1;
        i++;
    }
    fclose(fp1);   //to close the opened file
    if(x==0){     //if M is 0 then no name is found with given user name
        printf("No entries found with name %s\n",Name_M);
        return;
    }
    struct_count=i;
    FILE *fp2=fopen("phone.txt","w"); //file is opened to write into the file
    char type[50]=", This is your Data.";
    for(i=0;i<struct_count;i++)
    {   if (i+1==x) continue;	//if user input name is same as the name in the file then don't appending that name details
        else			//to append total data except the given input name details 
        {
            fprintf(fp2,"%s%s\n",people[i].Name,type);
            fprintf(fp2,"%s\t",people[i].Name);
            fprintf(fp2,"%d\n",people[i].numofnumbers);
            for(int j=0;j<people[i].numofnumbers;j++)
                fprintf(fp2,"%s\t%s\n",people[i].numbers[j].comment,people[i].numbers[j].mobnum);
        }
    }
    fclose(fp2);		//to close the opened file
        char choice,check;
        printf("what changes are you wanted to do.\nFor modifing Name choose 'N'\nFor modifing Comment choose 'C'\nFor modifing Mobile Number..etc choose 'M'\nfor QUIT 'Q'\n");
        printf("\nEnter your choice here:");
        scanf(" %c",&choice);
        if(choice=='M' || choice=='m')  //this if statement is used to modify phone number
        {   int value_number;
            printf("Enter which numbered phone number you want to modify(Ex: 1st,2nd,3rd......):");
            scanf(" %d",&value_number);  //takes input which numbered phonenumber as integer
            printf("Enter the new number:");
            scanf(" %s",people[x-1].numbers[value_number-1].mobnum); //takes the new number as modified input number
        }
        if(choice=='C'||choice=='c')	//this if statement is used to modify comments
        {   
            int value_number;
            printf("Enter which numbered comment you want to modify(Ex: 1st comment,2nd comment,3rd comment......):");
            scanf(" %d",&value_number);		//takes input which numbered commnent you want to modify as integer
            printf("Enter the comment:");
            scanf(" %[^\n]",people[x-1].numbers[value_number-1].comment); //takes input as modified comment 
        }
        if(choice=='N'||choice=='N')		//this if statement is used to modify name
        { 
            printf("Enter the new Name:");
            scanf(" %[^\n]",people[x-1].Name);	//takes input as modified name
        }	
    FILE *fp3=fopen("phone.txt","a");	//opening the file to append the modified data
    fprintf(fp3,"%s%s\n",people[x-1].Name,type);	//to append modified name
    fprintf(fp3,"%s\t",people[x-1].Name);
    fprintf(fp3,"%d\n",people[x-1].numofnumbers);	//to append the no of numbers
    for(int j=0;j<people[x-1].numofnumbers;j++)		//this for loop is used to append the modified comments and mobile numbers
        fprintf(fp3,"%s\t%s\n",people[x-1].numbers[j].comment,people[x-1].numbers[j].mobnum);
    fclose(fp3); //to close the opened file
}
int main(){
    int i=0;
    printf("Welcome to Directory\n");
    char c,c_1,ss[50],k[200];
    while(1==1)
    {
        char c;
        printf("Enter a command(S-Search A-Add M-Modify Q-Quit):");
        scanf("%c",&c);	//takes character from input to do some operations like Add Search Modify and also to Quit
        if(c=='A'||c=='a'){		//this if statement is used to add the data taken from user into file
            struct directory phn = readfromuser(c);	//to read the input data from user
            writetofile(phn);				//to add the input data into file
            clearmemory(phn);
        }
        if(c=='Q'||c=='q') return 0;	//this if is used to quit the program
        if(c=='S'||c=='s')		//this if is used to search the data in the file  
        {   
	    int q=0;
            char temp_str[50];
            scanf("%c",&c_1);	//to take the enter as character
            printf("Enter the Name you want to search for:");
            scanf("%[^\n]",temp_str);	//takes the person name you want to search
            FILE *fp=fopen("phone.txt","r");	//opening the file to read
            while (fscanf(fp,"%s %[^\n]\n",ss,k)!=EOF)
            {     
               
                int searching=search(temp_str,fp);	//it returns integer value 0 or 1 after going through search function
                if (searching==1) { q=1; }
            }
            if(q==0) printf("Given Contact not found\n");	//this if statement is true if q=0 that means given name is not there in the 									  file
            fclose(fp);		//to close the opened file
        }
        if(c=='M'||c=='m') modify();
        scanf("%c",&c);		//to take the enter as character
    }
}
