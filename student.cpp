# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
成绩
 */
typedef struct Record
{
    float math;
    float english;
    float count;
} Record;

/***
 * 学生
 */
typedef struct Student
{
    char no[20];
    char name[20];
    char gender[2];
    Record * record;
    Student * next;
    Student * parent;
} Student;

Student * first; //第一个学生

void addStudent(); //添加学生

void deleteStudent(); //删除学生

void updateStudent(); //更新学生

void sortStudent(); //排名学生

void avgStudent(); //统计平均分

void failedStudent(); //不及格的学生

void saveStudent(); //保存学生

void sortFileStudent(); //排序已经存在的学生

void insertStudentLinked(Student * s); //插入链表

Student * getStudentLastNode();//得到学生最后一个节点

int studentLength(); //有多少个学生 

char * getStudentNo(); //从用户输入得到学生的学号 

Student * getStudent(int index); //根据索引得到学生 

int main(int argc, char const *argv[])
{
    printf("*************菜单*******************\n");
    printf("1:教师入口\n");
    printf("2:学生入口\n"); 
    printf("********************************\n");
    
    char m = getchar();
    if(m == '1') { //学会选项
    	while(1) {
    		printf("1：录入学生信息和成绩\n");
			printf("2：增加学生信息和成绩\n");
			printf("3：删除学生信息和成绩\n");
			printf("4：修改学生信息和成绩\n");
			printf("5：按照总分或单科成绩对学生进行排名\n");
			printf("6：统计出男生或女生的平均分\n");
			printf("7：统计出单科不及格的学生信息和成绩\n");
			printf("8：保存学生成绩\n");
			printf("9：排序已经存在的学生成绩\n");
			
			getchar();
			m = getchar();
			 
			switch (m)
			{
			case '1':
			    addStudent();
			    break;
			case '2':
			    addStudent();
			    break;
			case '3':
				deleteStudent();
			    break;
			case '4':
				updateStudent();
			    break;
			case '5':
				sortStudent();
			    break;
			case '6':
			    break;
			case '7':
			    break;
			case '8':
			    break;
			case '9':
			    break;
			
			default:
			    break;
			}
		}
    } else if(m == '2') {   // 学生选项
         printf("1：按照学号或姓名查询学生成绩\n");
         printf("1：统计出总分或单科比自己分数高的学生信息和成绩\n");
    }

    return 0;
}



Student * getStudent(int index) { //根据索引得到学生 
	int len = studentLength();
	if(len <= index) return NULL;
	
	
	Student * temp;
	for(int i = 0; i < studentLength(); i ++) {
		if(i == index) return temp;
		else temp=temp->next;
	}
	return NULL;
} 


void sortStudent()  //排名学生
{
	
	if(first == NULL) {
		printf("没有学生\n\n");
		return;
	} 	
	
	///总分或单科成绩
	printf("1.按总分排名\n"); 
	printf("2.按单科成绩排名\n");
	
	getchar();
	char m = getchar();
	if(m == '1') {
	
		int len = studentLength();
	
		for(int i = 0; i < len;i++) {
			Student * sorting = getStudent(i);
			for (int j = 1; j < len; j ++) {
				Student * temp = getStudent(i);
				
				if(sorting->record->count < temp->record->count) {
					Student * a = sorting;
					
					sorting->parent->next = temp;
					temp->parent->next = a;
				}
			}
		}
	
	} else if(m=='2') {
		printf("1.数学\n"); 
		printf("2.英语\n");
		
		m = getchar();
		if(m == '1') {
				int len = studentLength();
		
				for(int i = 0; i < len;i++) {
					Student * sorting = getStudent(i);
					for (int j = 1; j < len; j ++) {
						Student * temp = getStudent(i);
						
						if(sorting->record->math < temp->record->math) {
							Student * a = sorting;
							
							sorting->parent->next = temp;
							temp->parent->next = a;
						}
					}
				}
		} else {
				int len = studentLength();
		
				for(int i = 0; i < len;i++) {
					Student * sorting = getStudent(i);
					for (int j = 1; j < len; j ++) {
						Student * temp = getStudent(i);
						
						if(sorting->record->english < temp->record->english) {
							Student * a = sorting;
							
							sorting->parent->next = temp;
							temp->parent->next = a;
						}
					}
				}
		}
	}
	
	printf("排序完成\n\n");
}


char * getStudentNo() {	
	printf("请输入学号:");
	char no[20];
	scanf("%s",&no);
	
	return &no[0]; 
} 

void updateStudent() {
	char * no = getStudentNo();
		
	Student * temp = first;
	for(int i = 0; i < studentLength(); i++) {
		if(strcmp(temp->no,no) == 0) {
			printf("学号：");
		    scanf("%s",&temp->no);
		
		    printf("姓名：");
		    scanf("%s",&temp->name);
		
		    printf("性别：");
		    scanf("%s",&temp->gender);
		
		    printf("数学：");
		    scanf("%f",&temp->record->math);
		
		    printf("英语：");
		    scanf("%f",&temp->record->english);
		
		    temp->record->count = temp->record->math + temp->record->english;
		
		    printf("更改成功\n\n"); 
		    return;
		}
	}
	
	printf("没有这个学生\n\n");
}


int studentLength() {
	if(first == NULL) return 0;
	
	int len = 0;
	
	Student * temp = first;
    while(1) {
    	++len;
        if(temp->next==NULL) return len;
    }
}

void insertStudentLinked(Student * s) {
    Student * lastStudent =  getStudentLastNode();
    if(lastStudent == NULL) first = s;
    else lastStudent->next = s;
}

Student * getStudentLastNode() {
    if(first == NULL) return NULL;

    Student * temp = first;
    while(1) {
        if(temp->next==NULL) return temp;
    }
}


void addStudent() {
    Student * newStudent = (Student *) malloc(sizeof(Student));
    newStudent->record = (Record *) malloc(sizeof(Record));
    
   
    if(first != NULL) {
    	Student * last = getStudentLastNode();
    	newStudent->parent = last; 
	}
    

    printf("学号：");
    scanf("%s",&newStudent->no);

    printf("姓名：");
    scanf("%s",&newStudent->name);

    printf("性别：");
    scanf("%s",&newStudent->gender);

    printf("数学：");
    scanf("%f",&newStudent->record->math);

    printf("英语：");
    scanf("%f",&newStudent->record->english);

    newStudent->record->count = newStudent->record->math + newStudent->record->english;

    insertStudentLinked(newStudent);
}


void deleteStudent() {

	char * no = getStudentNo();
	
	Student * temp = first;
	for(int i = 0; i < studentLength(); i++) {
		if(strcmp(temp->no,no) == 0) {
			temp->parent = temp->next;
			printf("删除%s成功\n\n",no);
			return;
		}
	}
	
	printf("删除%s失败，没有这个学生\n\n",no);
}
