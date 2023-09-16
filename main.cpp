
#include <winbgim.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
struct head_cell
{
    struct cell *head;
    int len ;
    char player_name[20];

                                    //len tool linklist ra neshan midahad.
}__attribute__((packed));
struct cell
{
    char name_cell[20];
    int x;
    int y;
    int energy;
    int index;
    struct cell *next;
}__attribute__((packed));
void save(int number_sorce , int arr_sorce[],int cell_number_1,int cell_number_2,int number_players,struct head_cell*head_cell_1,struct head_cell*head_cell_2)
{
    FILE *fb =fopen("info.bin","w");
    struct cell *head_copy_1 =head_cell_1->head;
    struct cell *head_copy_2 =head_cell_2->head;

    fwrite(arr_sorce, sizeof(int) ,3*number_sorce ,fb);
    fwrite(&number_players, sizeof(int) ,1 ,fb);
    if (number_players==1)
    {
        fwrite(&cell_number_1, sizeof(int) ,1 ,fb);
        while(head_copy_1!=NULL)
        {
             fwrite(head_copy_1, sizeof(struct cell) ,1 ,fb);
             head_copy_1=head_copy_1->next;
        }
    }
    if (number_players==2)
    {
        fwrite(&cell_number_1, sizeof(int) ,1 ,fb);
        fwrite(&cell_number_2, sizeof(int) ,1 ,fb);
        while(head_copy_1)
        {
             fwrite(head_copy_1, sizeof(struct cell) ,1 ,fb);
             head_copy_1=head_copy_1->next;
        }
        while(head_copy_2)
        {
             fwrite(head_copy_2, sizeof(struct cell) ,1 ,fb);
             head_copy_2=head_copy_2->next;
        }
    }
    fclose(fb);
}
int load(int number_sorce , int arr_sorce[],struct head_cell*head_cell_1,struct head_cell*head_cell_2)
{
    int number_player;
    int cell_number_1,cell_number_2;
    FILE *fb =fopen("info.bin","rb");
    head_cell_1->head = (struct cell *)malloc(sizeof(struct cell));
    struct cell *head_copy_1 =head_cell_1->head;
    fread(arr_sorce, sizeof(int) ,3*number_sorce ,fb);
    fread(&number_player, sizeof(int) ,1 ,fb);
    if (number_player==1)
    {
        fread(&cell_number_1, sizeof(int) ,1 ,fb);
        head_cell_1->len = cell_number_1;
        for(int i = 0 ; i<cell_number_1 ; i++)
        {
             if(i==0)
              {
                  fread(head_cell_1->head,sizeof(struct cell),1,fb);
                  head_cell_1->head->next = NULL ;
              }
             else
             {
                 struct cell * new_cell=(struct cell *) malloc(sizeof (struct cell));
                 fread(new_cell,sizeof(struct cell),1,fb);
                 head_copy_1->next=new_cell ;
                 head_copy_1 = head_copy_1 ->next ;
                 head_copy_1->next = NULL ;
             }
        }
    }
    if (number_player==2)
    {
        head_cell_2->head = (struct cell *)malloc(sizeof(struct cell));
        struct cell *head_copy_2 =head_cell_2->head;
        fread(&cell_number_1, sizeof(int) ,1 ,fb);
        head_cell_1->len = cell_number_1 ;
        fread(&cell_number_2, sizeof(int) ,1 ,fb);
        head_cell_2 ->len = cell_number_2;
        for(int i = 0 ; i<cell_number_1 ; i++)
        {
             if(head_cell_1->head == NULL)
              {
                  fread(head_cell_1->head,sizeof(struct cell),1,fb);
                  head_cell_1->head->next = NULL ;
              }
             else
             {
                 struct cell * new_cell=(struct cell *) malloc(sizeof (struct cell));
                 fread(new_cell,sizeof(struct cell),1,fb);
                 head_copy_1->next=new_cell ;
                 head_copy_1 = head_copy_1 ->next ;
                 head_copy_1->next = NULL ;
             }
        }
        for(int i = 0 ; i<cell_number_2 ; i++)
        {
             if(head_cell_2->head == NULL)

              {
                  fread(head_cell_2->head,sizeof(struct cell),1,fb);
                  head_cell_2->head->next = NULL ;
              }
             else
              {
                 struct cell * new_cell=(struct cell *) malloc(sizeof (struct cell));
                 fread(new_cell,sizeof(struct cell),1,fb);
                 head_copy_2->next=new_cell ;
                 head_copy_2 = head_copy_2 ->next ;
                 head_copy_2->next = NULL ;
              }
        }
    }
    fclose(fb);
    return number_player;

}
int sum_energy(struct head_cell *head_cell)
{
    int sum = 0;
    struct cell *head_copy = head_cell->head;
    while(head_copy)
    {
        sum+= head_copy ->energy;
        head_copy = head_copy->next ;
    }
    return sum ;
}
void print_map(int n, char table[])
{

	int arr_up[] = {40+100,40,80+100,40,96+100,64,80+100,88,40+100,88,24+100,64};
	int copy_up_arr[12];

	for(int k = 0 ; k<n ; k++)
	{

	for(int i =0 ; i<n ; i++)
	{
		for(int j =0 ; j<12 ; j++)
		{
			copy_up_arr[j] =arr_up[j] -((j%2)-1)*64*k+ (j%2)*i*64+32*(j%2)*(k%2);                   //64,64,32
		}
		char c;
		if (k==0) c = table[n-i-1];
        else c = table[k*n+n-i-1];
		int color ;
	    switch (c){
	    case '1':
	    	color = 3;       //sorce
	    	break ;
	    case '2':
	    	color = 4;         //mitosis
	    	break ;
	    case '3':
	    	color  = 2;         //forbidden
	    	break ;
	    case '4':
	    	color = 7;          //normal
	    	break ;
			}
		setcolor(0);
		setfillstyle(SOLID_FILL , color);                       //
		fillpoly (6 , copy_up_arr);




	}
    setcolor(3);
	setfillstyle(SOLID_FILL ,3);
	circle(30,95,20);
	floodfill(35,98,3);
	outtextxy(53,90,"Sorce");

    setcolor(4);
	setfillstyle(SOLID_FILL ,4);
	circle(30,145,20);
	floodfill(35,148,4);
	outtextxy(53,140,"Mitosis");

    setcolor(2);
	setfillstyle(SOLID_FILL ,2);
	circle(30,195,20);
	floodfill(35,198,2);
	outtextxy(53,190,"Block");

    setcolor(7);
	setfillstyle(SOLID_FILL ,7);
	circle(30,245,20);
	floodfill(35,248,7);
	outtextxy(53,240,"Normal");
	}
//	simple_print_cell(cell , n);

}
void print_cell(struct head_cell *head_cell , int n,int color)
{
    if (head_cell->head==NULL) return ;
    struct cell * head_copy = head_cell ->head;
    if (color==0)
    {
        setbkcolor(0);
        setcolor(7);
    }
    if (color==1)
    {
        setbkcolor(5);
        setcolor(7);
    }
    while (head_copy!= NULL )
    {

        char buffer[10];
        char buffer2[4];
        itoa(head_copy->energy,buffer2,10);
        itoa(head_copy->index,buffer,10);
        strcat(buffer,">");
        strcat(buffer,buffer2);
       outtextxy(150+64*head_copy->x , 60+64*(n-head_copy->y-1)+32*(head_copy->x%2),buffer);
        head_copy = head_copy ->next ;
    }
}
int check_uncell(int n , int x , int y ,char table[],struct head_cell *head_cell_1,struct head_cell *head_cell_2)
{                                                                                                //correcr
    struct cell *head_copy1 = head_cell_1->head;
    struct cell *head_copy2 = head_cell_2->head;

    while(head_copy1!=NULL)
    {
        if (head_copy1 -> x == x)
            if(head_copy1 ->y == y)
                return 0 ;
        head_copy1 = head_copy1 ->next;
    }
    if (head_copy2 ==NULL) return 1;
    while(head_copy2!=NULL)
    {
        if (head_copy2 -> x == x)
            if(head_copy2 ->y == y)
                return 0 ;
        head_copy2 = head_copy2 ->next;
    }

    return 1;
}
int check_unblock (int n , int x , int y ,char table[])                    //correct             //block nabashad va az naghse kharj nashavad
{

    if (table[n*x+y]=='3') return 0 ;
    if (x < 0 || x >= n || y < 0 ||y >= n) return 0;
    return 1;

}
void rand_move( int n ,char table[] ,struct head_cell *head_cell,struct head_cell *head_cell_another )
{
    struct cell *head_copy = head_cell -> head ;
    srand(time(0)) ;
    int x,y ;                                                                                                    //correcr
    while (head_copy != NULL)
    {
        x = rand()%n ;
        y = rand()%n ;
                                                                                    // makani random baraye hae sellol dar ebtedaye bazi ijad mikonad.
        if ( check_unblock (n ,x , y , table)==1 && check_uncell( n ,  x ,  y , table,head_cell,head_cell_another)==1  )
           {
               head_copy ->x = x ;
               head_copy ->y = y ;
               head_copy = head_copy ->next ;
           }

    }
}
void add_cell(struct head_cell *head_cell )
{
    struct cell *new_cell = (struct cell *) malloc(sizeof (struct cell));                       //correct
    if (head_cell ->head ==NULL)
    {
         head_cell->head = new_cell;
         head_cell->head->next=NULL ;
         scanf("%s",head_cell->head->name_cell);
         head_cell ->head ->energy = 0 ;
         head_cell ->len++;
         head_cell->head->index =head_cell ->len ;

    }
    else
    {
    struct cell *head_copy = head_cell ->head ;
    while(head_copy ->next !=NULL)
        head_copy =head_copy ->next ;
    head_copy->next = new_cell ;
    scanf("%s",new_cell->name_cell);
    new_cell -> energy = 0 ;
    new_cell ->next = NULL ;
    head_cell ->len++;
    new_cell ->index = head_cell ->len ;
    }

}
struct cell * find_cell(struct head_cell *head_cell)
{
    int a ;
   // printf("please enter the index of your chosen cell\n");
    scanf("%d",&a);
    struct cell *head_copy = head_cell ->head ;
    while (head_copy !=NULL)
    {
        if (head_copy ->index == a )
        {
            return head_copy ;
            break ;
        }
        head_copy = head_copy ->next ;

    }

            printf("Cell not found\n");
            printf("Choose another index.\n");
            find_cell(head_cell);
            //return NULL ;

};
void split(int n,struct cell *cell , char table[],struct head_cell *head_cell,int arr_condition[3][7])
{
   int k,j;
   while(1)
   {

         k =rand()%7 ;
         if (arr_condition[2][k]==1)
         {
             printf("Enter the name of first new cell : \n");
             scanf("%s",cell->name_cell);
             cell->x =arr_condition[0][k];
             cell->y = arr_condition[1][k];
             cell->energy = 40 ;
             break;
         }
   }
    printf("Enter the name of second new cell : \n");
    add_cell(head_cell);
    struct cell * head_copy = head_cell->head;
    while(head_copy->next != NULL) head_copy = head_copy->next;
   while(1)
   {
         j =rand()%7;
         if (arr_condition[2][j]==1 && j!= k)
         {
             head_copy->energy = 40 ;
             head_copy->x =arr_condition[0][j];
             head_copy->y = arr_condition[1][j];
             break;
         }
   }

}
int check_eneergy_boost(int number_sorce , struct cell *cell , int arr_sorce[])
{

    for (int i = 0 ; i<number_sorce ; i++)
    {
        if (arr_sorce[3*i+1]==cell->x && arr_sorce[3*i+2]==cell ->y && arr_sorce[3*i]==0) return 0 ;

       if (arr_sorce[3*i+1]==cell->x && arr_sorce[3*i+2]==cell ->y &&cell->energy ==100) return 0 ;
    }
    return 1 ;
}
int boost_energy(int number_sorce , struct cell *cell , int arr_sorce[] )
{
    for (int i = 0 ; i<number_sorce ; i++)
    {
        if (arr_sorce[3*i+1]==cell->x && arr_sorce[3*i+2]==cell ->y && arr_sorce[3*i]>=15 && cell ->energy <=85)
        {
              arr_sorce[3*i]-=15 ;
              cell ->energy +=15;
              return 1;
              break ;
        }
        else if (arr_sorce[3*i+1]==cell->x && arr_sorce[3*i+2]==cell ->y && arr_sorce[3*i]>=15 && cell ->energy <100)
        {
           arr_sorce[3*i]-=(100 - cell->energy) ;
           cell->energy =100 ;
           return 1;
           break ;
        }
        else if (arr_sorce[3*i+1]==cell->x && arr_sorce[3*i+2]==cell ->y && arr_sorce[3*i]<15 && cell ->energy <100)
        {
            cell ->energy += arr_sorce[3*i] ;
            arr_sorce[3*i] = 0 ;
            return 1;
            break ;
        }

    }
        printf("boosting energy is not possible .");
        printf("Try sometheing else\n");
        return 0 ;
}
int check_split_condition(int n,struct cell *cell , char table[],struct head_cell *head_cell,int arr_condition[3][7],struct head_cell *head_cell_another)               //correct
{
   int a = cell ->x ;
   int b = cell ->y ;                                                                                                  //arr_condition = khanehaye hamsayei ke ghabliat enteghal daran.
   int c = (a%2 == 0)? 1 : 0;                                                                                           // dar ebteda hame khanehaye arr_condition bayad sefr bashad.(tavajoh)
   arr_condition[0][0]=arr_condition[0][1] = arr_condition[0][2] = a;
   arr_condition[0][3]=arr_condition[0][4]=a+1;
   arr_condition[0][5]=arr_condition[0][6]=a-1;
   arr_condition[1][0]=b;
   arr_condition[1][1]=b+1;
   arr_condition[1][2]=b-1;
   arr_condition[1][3]=arr_condition[1][5]= b+c;
   arr_condition[1][4]=arr_condition[1][6]= b+c-1;

   arr_condition[2][0]=1;             //makan avalie sellol ham baraye taqsim ghabl estefadast.
   if (check_unblock (n ,a,b+1, table)==1 && check_uncell( n ,a,b+1 ,table,head_cell,head_cell_another)==1) arr_condition[2][1]=1;        //hadeaghal 2 khane khali atraf sellooli ke mikhahad taqsim shavad bayad bashad.
   if (check_unblock (n ,a,b-1, table)==1 && check_uncell( n ,a,b-1 ,table,head_cell,head_cell_another)==1) arr_condition[2][2]=1;
   if (check_unblock (n ,a+1,b+c, table)==1 && check_uncell( n ,a+1,b+c ,table,head_cell,head_cell_another)==1) arr_condition[2][3]=1;
   if (check_unblock (n ,a+1,b+c-1, table)==1 && check_uncell( n ,a+1,b+c-1 ,table,head_cell,head_cell_another)==1) arr_condition[2][4]=1;
   if (check_unblock (n ,a-1,b+c, table)==1 && check_uncell( n ,a-1,b+c ,table,head_cell,head_cell_another)==1) arr_condition[2][5]=1;
   if (check_unblock (n ,a-1,b+c-1, table)==1 && check_uncell( n ,a-1,b+c-1 ,table,head_cell,head_cell_another)==1) arr_condition[2][6]=1;
   int sum = 0;
   for(int i=0 ;i<7  ;i++ ,sum+=arr_condition[2][i]);
   if (sum>=2 && cell ->energy >= 80 &&table[n*cell->x+cell->y]=='2') return 1;
   return 0 ;
}
int mov(int n,struct cell *cell , char table[],struct head_cell *head_cell,struct head_cell *head_cell_another)
{
   // struct cell*head_copy = head_cell ->head ;
   // for (int i =0 ; i<index -1 ; i++ ,head_copy = head_copy->next);
    int input ;
    printf("Choose your direction.\n") ;
    printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n[7]Stay\n");
    scanf("%d",&input);
    int b ;
    switch(input){
    case 1 :
        if(check_unblock (n ,cell -> x,cell ->y+1, table)==1 && check_uncell( n , cell -> x,cell ->y +1 , table,head_cell,head_cell_another)==1)
        {
            cell ->y ++ ;
            return 1;
        }
        break;
    case 2 :
        if(check_unblock (n ,cell -> x,cell ->y-1, table)==1 && check_uncell( n , cell -> x,cell ->y-1 , table,head_cell,head_cell_another)==1)
        {
            cell ->y-- ;
            return 1;
        }
        break;
    case 3 :

        if (cell ->x %2 ==0) b=1;
        else b = 0 ;
        if(check_unblock (n ,cell -> x+1,cell ->y+b, table)==1 && check_uncell( n , cell ->x+1,cell ->y+b , table,head_cell,head_cell_another)==1)
        {
            cell ->x +=1 ;
            cell ->y +=b;

            return 1;
        }
        break;
    case 4 :
        if (cell ->x %2==0) b=1;
        else
            b = 0;
        if(check_unblock (n ,cell -> x-1,cell ->y+b, table)==1 && check_uncell( n , cell-> x-1,cell ->y+b , table,head_cell,head_cell_another)==1)
        {
            cell ->x --;
            cell ->y +=b;

            return 1;
        }
        break;
    case 5 :
        if(cell->x %2 == 0 ) b = 0;
        else b = -1;
        if(check_unblock (n ,cell -> x+1,cell ->y+b, table)==1 && check_uncell( n , cell -> x+1,cell->y+b , table,head_cell,head_cell_another)==1)
        {
            cell ->y +=b ;
            cell-> x ++;

            return 1;
        }
        break;
    case 6 :
        if(cell->x%2 == 0) b=0 ;
        else b = -1;
        if(check_unblock (n ,cell -> x-1,cell ->y+b, table)==1 && check_uncell( n , cell -> x-1,cell ->y+b , table,head_cell,head_cell_another)==1)
        {
            cell->x --;
            cell ->y +=b ;

            return 1;
        }
        break ;
    case 7 :
        return 1 ;
        break;

    }
     printf("Moving to the selected direction is not possible.");
     printf("Try sometheing else\n");
     return 0 ;
}
void make_arr_sorce(int n  ,int number_sorce ,char table[],int arr_sorce[])           //correct        //arr_sorce[0][i] = energy manba i.
{
    int counter = 0 ;
    for(int j = 0 ; j <n*n ; j++)
    {
        if (table[j]== '1')
        {
            int copy_j = j;
            arr_sorce[3*counter] = 100;
            arr_sorce[3*counter+1] =(int)(copy_j/n);
            arr_sorce[3*counter+2] = j - (arr_sorce[3*counter+1]*n) ;
            counter++;
        }

    }
}
void handler_player(int n ,struct cell *cell,struct head_cell*head_cell,char table[],int number_sorce,int arr_sorce[],int arr_condition[3][7],struct head_cell *head_cell_another)
{
    int a ;
    printf("[1]Move\n[2]split\n[3]Boost energy\n[4]Select another cell\n");
    scanf("%d",&a);
    switch(a){
    case 1 :
       if (mov(n,cell ,table,head_cell,head_cell_another)==0)

        handler_player( n ,cell,head_cell, table, number_sorce,arr_sorce, arr_condition,head_cell_another);



        break ;
    case 2 :
        if (check_split_condition( n,cell ,table,head_cell,arr_condition,head_cell_another)==0 )
        {   printf("mitosis for selected cell is not possible , try something else .\n");
            handler_player( n ,cell,head_cell, table, number_sorce,arr_sorce, arr_condition,head_cell_another);
            break;
        }
        split( n,cell , table,head_cell,arr_condition);
        break ;
    case 3 :
       if ( boost_energy(number_sorce ,cell , arr_sorce )== 0) handler_player( n ,cell,head_cell, table, number_sorce,arr_sorce, arr_condition,head_cell_another);
        print_map(n, table);
        break ;
    case 4:
        printf("Enter the index of another cell.\n");
        struct cell *cell = find_cell(head_cell);
        printf("%s\n",cell->name_cell);
        handler_player( n ,cell,head_cell, table, number_sorce,arr_sorce, arr_condition,head_cell_another);
        break;


        }
    }                                                                     //check mikond ke dar khane selloli az ghabl  nabashad.
int main()
{

    initwindow(700, 700);
	setbkcolor(0);
    FILE *fp =fopen("map.bin","rb");
    unsigned int n;
    fread(&n , sizeof(unsigned int) ,1,fp);
    char table[n*n];
    if (fp==NULL)
    {
        printf("map.bin can not be open");
        return -1;
    }
    fread(table, sizeof(char) ,n*n ,fp);
    int number_sorce=0 ;
    for(int j=0 ; j<n*n ; j++)
        if (table[j]=='1')
            number_sorce++;
    fclose(fp);
    int arr_sorce[3*number_sorce];
    make_arr_sorce(n  ,number_sorce ,table, arr_sorce) ;
    struct head_cell *head_cell_1 =(struct head_cell *) malloc(sizeof(struct head_cell));
    head_cell_1->head = NULL ;
    head_cell_1 ->len =0 ;
    struct head_cell *head_cell_2 =(struct head_cell *) malloc(sizeof(struct head_cell));
    head_cell_2->head = NULL ;
    head_cell_2 ->len =0 ;
    int input ;
    printf("[1]Load\n[2]New single player game\n[3]New Multiplayer game\n[4]Exit\n");
    scanf("%d",&input);


    switch(input)
        {
        case 2:
           int number_cell;
           print_map(n, table);
           printf("What is your name?\n");
           scanf("%s",head_cell_1->player_name);
           printf("Hello %s,enter the number of your cells.\n",head_cell_1->player_name);
           scanf("%d",&number_cell);
           printf("What are your cells name?\n");
           for(int i =0 ; i<number_cell ;i++)
                add_cell(head_cell_1);
           rand_move(n , table ,head_cell_1,head_cell_2);
           print_map(n, table);
           print_cell(head_cell_1 , n,0);
           save(number_sorce , arr_sorce,head_cell_1->len,0,1,head_cell_1,head_cell_2);
           while(1)
           {
               kbhit();
               print_map(n, table);
               print_cell(head_cell_1 , n,0);
               int arr_condition[3][7];
               for(int i= 0 ; i<7 ;i++)
               arr_condition[2][i]= 0;
               printf("1)Enter the index of one cell\n");
               struct cell *cell = find_cell(head_cell_1);
               printf("%s\n",cell->name_cell);
               handler_player( n ,cell,head_cell_1, table, number_sorce,arr_sorce, arr_condition,head_cell_2);
               save(number_sorce , arr_sorce,head_cell_1->len,0,1,head_cell_1,head_cell_2);
           }
        case 3:
           int number_cell_1;
           print_map(n, table);
           printf("(First Player)\nWhat is your name?\n");
           scanf("%s",head_cell_1->player_name);
           printf("Hello %s,enter the number of your cells.\n",head_cell_1->player_name);
           scanf("%d",&number_cell_1);
           printf("What are your cells name?\n");
           for(int i =0 ; i<number_cell_1 ;i++)
                add_cell(head_cell_1);
           rand_move(n , table ,head_cell_1,head_cell_2);
           print_map(n, table);
           print_cell(head_cell_1 , n,0);
           int number_cell_2;
           printf("(Second Player)\nWhat is your name?\n");
           scanf("%s",head_cell_2->player_name);
           printf("Hello %s,enter the number of your cells.\n",head_cell_2->player_name);
           scanf("%d",&number_cell_2);
           printf("What are your cells name?\n");
           for(int i =0 ; i<number_cell_2 ;i++)
                add_cell(head_cell_2);
           rand_move(n , table ,head_cell_2,head_cell_1);
           print_map(n, table);
           print_cell(head_cell_1 , n,0);
           print_cell(head_cell_2 , n,0);
           save(number_sorce , arr_sorce,head_cell_1->len,head_cell_2->len,2,head_cell_1,head_cell_2);
           while(1)
           {
               kbhit();
               print_map(n, table);
               print_cell(head_cell_1 , n,0);
               print_cell(head_cell_2 , n,1);
               int arr_condition[3][7];
               for(int i= 0 ; i<7 ;i++)
               arr_condition[2][i]= 0;
               printf("Enter the index of one cell %s(you are black and your total energy = %d):)\n",head_cell_1->player_name,sum_energy(head_cell_1));
               struct cell *cell_1 = find_cell(head_cell_1);
               printf("%s\n",cell_1->name_cell);
               handler_player( n ,cell_1,head_cell_1, table, number_sorce,arr_sorce, arr_condition,head_cell_2);
               print_map(n, table);
               print_cell(head_cell_1 , n,0);
               print_cell(head_cell_2 , n,1);
               printf("Enter the index of one cell %s(you are pink and  and your total energy = %d):)\n",head_cell_2->player_name,sum_energy(head_cell_2));
               struct cell *cell_2 = find_cell(head_cell_2);
               printf("%s\n",cell_2->name_cell);
               handler_player( n ,cell_2,head_cell_2, table, number_sorce,arr_sorce, arr_condition,head_cell_1);
               save(number_sorce , arr_sorce,head_cell_1->len,head_cell_2->len,2,head_cell_1,head_cell_2);
           }
           break;
        case 1:
           int number_players = load(number_sorce,arr_sorce,head_cell_1,head_cell_2);
           if (number_players==1)
           {
               printf("What is your name?\n");
               scanf("%s",head_cell_1->player_name);
               while(1)
               {
                   kbhit();
                   print_map(n, table);
                   print_cell(head_cell_1 , n,0);
                   int arr_condition[3][7];
                   for(int i= 0 ; i<7 ;i++)
                   arr_condition[2][i]= 0;
                   printf("1)Enter the index of one cell\n");
                   struct cell *cell = find_cell(head_cell_1);
                   printf("%s\n",cell->name_cell);
                   handler_player( n ,cell,head_cell_1, table, number_sorce,arr_sorce, arr_condition,head_cell_2);
                   save(number_sorce , arr_sorce,head_cell_1->len,0,1,head_cell_1,head_cell_2);
               }

           }
           if (number_players==2)
          {
           printf("(First Player)\nWhat is your name?\n");
           scanf("%s",head_cell_1->player_name);
           printf("(Second Player)\nWhat is your name?\n");
           scanf("%s",head_cell_2->player_name);
           printf("Hello %s,enter the number of your cells.\n",head_cell_2->player_name);
           while(1)
           {
               kbhit();
               print_map(n, table);
               print_cell(head_cell_1 , n,0);
               print_cell(head_cell_2 , n,1);
               int arr_condition[3][7];
               for(int i= 0 ; i<7 ;i++)
               arr_condition[2][i]= 0;
               printf("Enter the index of one cell %s(you are black and your total energy = %d):)\n",head_cell_1->player_name,sum_energy(head_cell_1));
               struct cell *cell_1 = find_cell(head_cell_1);
               printf("%s\n",cell_1->name_cell);
               handler_player( n ,cell_1,head_cell_1, table, number_sorce,arr_sorce, arr_condition,head_cell_2);
               save(number_sorce , arr_sorce,head_cell_1->len,head_cell_2->len,2,head_cell_1,head_cell_2);
               print_map(n, table);
               print_cell(head_cell_1 , n,0);
               print_cell(head_cell_2 , n,1);
               printf("Enter the index of one cell %s(you are pink and  and your total energy = %d):)\n",head_cell_2->player_name,sum_energy(head_cell_2));
               struct cell *cell_2 = find_cell(head_cell_2);
               printf("%s\n",cell_2->name_cell);
               handler_player( n ,cell_2,head_cell_2, table, number_sorce,arr_sorce, arr_condition,head_cell_1);
               save(number_sorce , arr_sorce,head_cell_1->len,head_cell_2->len,2,head_cell_1,head_cell_2);
           }
          }
            break ;
        }

    return 0;
}
