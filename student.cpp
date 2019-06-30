# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
�ɼ�
 */
typedef struct Record
{
    float math;
    float english;
    float count;
} Record;

/***
 * ѧ��
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

Student * first; //��һ��ѧ��

void addStudent(); //���ѧ��

void deleteStudent(); //ɾ��ѧ��

void updateStudent(); //����ѧ��

void sortStudent(); //����ѧ��

void avgStudent(); //ͳ��ƽ����

void failedStudent(); //�������ѧ��

void saveStudent(); //����ѧ��

void sortFileStudent(); //�����Ѿ����ڵ�ѧ��

void insertStudentLinked(Student * s); //��������

Student * getStudentLastNode();//�õ�ѧ�����һ���ڵ�

int studentLength(); //�ж��ٸ�ѧ�� 

char * getStudentNo(); //���û�����õ�ѧ����ѧ�� 

Student * getStudent(int index); //���������õ�ѧ�� 

int main(int argc, char const *argv[])
{
    printf("*************�˵�*******************\n");
    printf("1:��ʦ���\n");
    printf("2:ѧ�����\n"); 
    printf("********************************\n");
    
    char m = getchar();
    if(m == '1') { //ѧ��ѡ��
    	while(1) {
    		printf("1��¼��ѧ����Ϣ�ͳɼ�\n");
			printf("2������ѧ����Ϣ�ͳɼ�\n");
			printf("3��ɾ��ѧ����Ϣ�ͳɼ�\n");
			printf("4���޸�ѧ����Ϣ�ͳɼ�\n");
			printf("5�������ֻܷ򵥿Ƴɼ���ѧ����������\n");
			printf("6��ͳ�Ƴ�������Ů����ƽ����\n");
			printf("7��ͳ�Ƴ����Ʋ������ѧ����Ϣ�ͳɼ�\n");
			printf("8������ѧ���ɼ�\n");
			printf("9�������Ѿ����ڵ�ѧ���ɼ�\n");
			
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
    } else if(m == '2') {   // ѧ��ѡ��
         printf("1������ѧ�Ż�������ѯѧ���ɼ�\n");
         printf("1��ͳ�Ƴ��ֻܷ򵥿Ʊ��Լ������ߵ�ѧ����Ϣ�ͳɼ�\n");
    }

    return 0;
}



Student * getStudent(int index) { //���������õ�ѧ�� 
	int len = studentLength();
	if(len <= index) return NULL;
	
	
	Student * temp;
	for(int i = 0; i < studentLength(); i ++) {
		if(i == index) return temp;
		else temp=temp->next;
	}
	return NULL;
} 


void sortStudent()  //����ѧ��
{
	
	if(first == NULL) {
		printf("û��ѧ��\n\n");
		return;
	} 	
	
	///�ֻܷ򵥿Ƴɼ�
	printf("1.���ܷ�����\n"); 
	printf("2.�����Ƴɼ�����\n");
	
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
		printf("1.��ѧ\n"); 
		printf("2.Ӣ��\n");
		
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
	
	printf("�������\n\n");
}


char * getStudentNo() {	
	printf("������ѧ��:");
	char no[20];
	scanf("%s",&no);
	
	return &no[0]; 
} 

void updateStudent() {
	char * no = getStudentNo();
		
	Student * temp = first;
	for(int i = 0; i < studentLength(); i++) {
		if(strcmp(temp->no,no) == 0) {
			printf("ѧ�ţ�");
		    scanf("%s",&temp->no);
		
		    printf("������");
		    scanf("%s",&temp->name);
		
		    printf("�Ա�");
		    scanf("%s",&temp->gender);
		
		    printf("��ѧ��");
		    scanf("%f",&temp->record->math);
		
		    printf("Ӣ�");
		    scanf("%f",&temp->record->english);
		
		    temp->record->count = temp->record->math + temp->record->english;
		
		    printf("���ĳɹ�\n\n"); 
		    return;
		}
	}
	
	printf("û�����ѧ��\n\n");
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
    

    printf("ѧ�ţ�");
    scanf("%s",&newStudent->no);

    printf("������");
    scanf("%s",&newStudent->name);

    printf("�Ա�");
    scanf("%s",&newStudent->gender);

    printf("��ѧ��");
    scanf("%f",&newStudent->record->math);

    printf("Ӣ�");
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
			printf("ɾ��%s�ɹ�\n\n",no);
			return;
		}
	}
	
	printf("ɾ��%sʧ�ܣ�û�����ѧ��\n\n",no);
}
