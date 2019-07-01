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
    char * no;
    char * name;
    char * gender;
    Record * record;
    Student * next;
    Student * parent;
} Student;

Student * first = NULL; //��һ��ѧ��

void addStudent(); //���ѧ��

void deleteStudent(); //ɾ��ѧ��

void updateStudent(); //����ѧ��

void sortStudent(); //����ѧ��

void avgStudent(); //ͳ��ƽ����

void failedStudent(); //�������ѧ��

void saveStudent(Student * head); //����ѧ��

void sortFileStudent(); //�����Ѿ����ڵ�ѧ��

void insertStudentLinked(Student * s); //��������

Student * getStudentLastNode();//�õ�ѧ�����һ���ڵ�

int studentLength(Student * head); //�����ж��ٸ�ѧ��

char * getStudentNo(); //���û�����õ�ѧ����ѧ��

Student * getStudent(Student * head,int index); //���������õ�ѧ��

Student * getStudentLastNodeByHead(Student * head);

void sortByCount(Student * head); //ͨ���ܷ���Ѱ

char **split(char sep, const char *str, int *size); //����һ�� char *arr[], sizeΪ��������ĳ���

void queryMark();

void queryHigh(Student *pStudent);


const  char * cjfile = "d:/chengji.txt";

int main(int argc, char const *argv[])
{
    FILE * file = fopen(cjfile,"rw");
    if(file == NULL) {
        printf("��ȡʧ��\n");
    } else {
        char StrLine[1024];
        int size;

        while (!feof(file)) {
            fgets(StrLine, 1024, file);  //��ȡһ��
            char **arr = split('\t', StrLine, &size);
            int i;

            Student *student = (Student *) malloc(sizeof(Student));
            Record *record = (Record *) malloc(sizeof(Record));

            student->next = NULL;
            student->parent = NULL;
            student->record = record;

            student->no = arr[0];
            student->name = arr[1];
            student->gender = arr[2];

            record->math = atof(arr[3]);
            record->english = atof(arr[4]);
            record->count = atof(arr[5]);


            if (first == NULL) {
                first = student;
            } else {
                Student *last = getStudentLastNodeByHead(first);
                last->next = student;
                student->parent = last;
            }
        }
        //�ر��ļ�
        fclose(file);
    }

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
                    avgStudent();
                    break;
                case '7':
                    failedStudent();
                    break;
                case '8':
                    saveStudent(first);
                    break;
                case '9':
                    sortFileStudent();
                    break;
                default:
                    break;
            }
        }
    } else if(m == '2') {   // ѧ��ѡ��
        Student * login;
        printf("1.���������ѧ�ţ�");
        char no[20] ;
        scanf("%s",no);

        int len = studentLength(first);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(strcmp(s->no,no)==0) {
                login = s;
                break;
            }
        }

        if(login == NULL) {
            printf("û�����ѧ��");
            return 0;
        }

        while(1) {

            printf("1������ѧ�Ż�������ѯѧ���ɼ�\n");
            printf("2��ͳ�Ƴ��ֻܷ򵥿Ʊ��Լ������ߵ�ѧ����Ϣ�ͳɼ�\n");

            getchar();
            char c =getchar();
            if(c=='1') {
                queryMark();
            } else if(c=='2') {
                queryHigh(login);
            }
        }
    }
    return 0;
}

void queryHigh(Student *login) { //��ѯ���ߵ�
    getchar();

    int len = studentLength(first);
    char data[20];

    printf("1.���Ʋ�ѯ.\n");
    printf("2.�ܷ�\n");
    int m = getchar();

    if(m=='1') {
        printf("1.��ѧ\n");
        printf("2.Ӣ��\n");
        getchar();
        m=getchar();
        if(m == '1') {
            int len = studentLength(first);
            for(int i = 0; i < len;i++) {
                Student *s = getStudent(first, i);
                if(s->record->math > login->record->math) {
                    printf("ѧ�ţ�%s,������%s,�Ա�%s,��ѧ��%f,Ӣ�%f,�ܷ֣�%f\n",s->no,s->name,s->gender,
                           s->record->math,s->record->english,s->record->count);
                }
            }
        } else if(m='2') {
            int len = studentLength(first);
            for(int i = 0; i < len;i++) {
                Student *s = getStudent(first, i);
                if(s->record->english > login->record->english) {
                    printf("ѧ�ţ�%s,������%s,�Ա�%s,��ѧ��%f,Ӣ�%f,�ܷ֣�%f\n",s->no,s->name,s->gender,
                           s->record->math,s->record->english,s->record->count);
                }
            }
        }


    } else if(m=='2') { //�ܷ�
        int len = studentLength(first);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(s->record->count > login->record->count) {
                printf("ѧ�ţ�%s,������%s,�Ա�%s,��ѧ��%f,Ӣ�%f,�ܷ֣�%f\n",s->no,s->name,s->gender,
                       s->record->math,s->record->english,s->record->count);
            }
        }
    }
}

void queryMark() { //��ѯ����
    getchar();

    int len = studentLength(first);
    char data[20];

    printf("1.ѧ��\n");
    printf("2.����\n");
    int m = getchar();

    if(m=='1') {
        printf("������ѧ�ţ�");
        scanf("%s",data);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(strcmp(s->no,data)==0) {
                printf("��ѧ��%f,Ӣ�%f,�ܷ֣�%f\n",s->record->math,s->record->english,s->record->count);
                return;
            }
        }
    } else if(m=='2') {
        printf("������ѧ�ţ�");
        scanf("%s",data);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(strcmp(s->name,data)==0) {
                printf("��ѧ��%f,Ӣ�%f,�ܷ֣�%f\n",s->record->math,s->record->english,s->record->count);
            }
        }
    }
}

void sortByCount(Student * head) {
    int len = studentLength(head);

    for(int i = 0; i < len;i++) {
        Student * sorting = getStudent(head,i);
        for (int j = i+1; j < len; j ++) {
            Student * temp = getStudent(head,j);

            if(sorting->record->count < temp->record->count) {
                Student * swap = (Student*) malloc(sizeof(Student));
                swap->name = sorting->name;
                swap->no=sorting->no;
                swap->gender=sorting->gender;
                swap->record=sorting->record;


                sorting->no = temp->no;
                sorting->name = temp->name;
                sorting->gender=temp->gender;
                sorting->record=temp->record;

                temp->no = swap->no;
                temp->name = swap->name;
                temp->gender = swap->gender;
                temp->record = swap->record;
            }
        }
    }
}

void sortFileStudent() { //���ļ��е�ѧ������
    FILE * file = fopen(cjfile,"rw");
    if(file == NULL) {
        printf("��ȡʧ��\n");
    } else {
        char StrLine[1024];
        int size;

        Student * head = NULL;
        while (!feof(file))
        {
            fgets(StrLine, 1024, file);  //��ȡһ��
            char **arr = split('\t', StrLine, &size);
            int i;

            Student *student = (Student *) malloc(sizeof(Student));
            Record * record = (Record *) malloc(sizeof(Record));

            student->record = record;

            student->no = arr[0];
            student->name = arr[1];
            student->gender = arr[2];

            record->math = atof(arr[3]);
            record->english = atof(arr[4]);
            record->count = atof(arr[5]);


            if(head == NULL) {
                head = student;
            } else {
                Student * last = getStudentLastNodeByHead(head);
                last->next = student;
                student->parent = last;
            }
        }

        //�ر��ļ�
        fclose(file);

        sortByCount(head);

        saveStudent(head);
    }
}


//����һ�� char *arr[], sizeΪ��������ĳ���
char **split(char sep, const char *str, int *size)
{
    int count = 0, i;
    for(i = 0; i < strlen(str); i++)
    {
        if (str[i] == sep)
        {
            count ++;
        }
    }

    char **ret = (char**)calloc(++count, sizeof(char *));

    int lastindex = -1;
    int j = 0;

    for(i = 0; i < strlen(str); i++)
    {
        if (str[i] == sep)
        {
            ret[j] = (char*)calloc(i - lastindex, sizeof(char)); //�����Ӵ�����+1���ڴ�ռ�
            memcpy(ret[j], str + lastindex + 1, i - lastindex - 1);
            j++;
            lastindex = i;
        }
    }
    //�������һ���Ӵ�
    if (lastindex <= strlen(str) - 1)
    {
        ret[j] = (char*)calloc(strlen(str) - lastindex, sizeof(char));
        memcpy(ret[j], str + lastindex + 1, strlen(str) - 1 - lastindex);
        j++;
    }

    *size = j;

    return ret;
}


void saveStudent(Student * head) { //����ѧ��

    if(studentLength(head) == 0) {
        printf("û��ѧ��\n\n");
        return;
    }

    FILE * file = fopen(cjfile,"w");
    if(file != NULL) {
        for (int i = 0; i < studentLength(head); i++) {
            Student * s = getStudent(head,i);
            fprintf(file,s->no);
            fprintf(file,"\t");

            fprintf(file,s->name);
            fprintf(file,"\t");

            fprintf(file,s->gender);
            fprintf(file,"\t");

            char buf[20];
            char * mathString = gcvt(s->record->math,4,buf);
            fprintf(file,mathString);
            fprintf(file,"\t");

            char * englishString = gcvt(s->record->english,4,buf);
            fprintf(file,englishString);
            fprintf(file,"\t");

            char * countString = gcvt(s->record->count,4,buf);
            fprintf(file,countString);
            fprintf(file,"\n");
        }

        fflush(file);
        fclose(file);

        printf("����ɹ�\n");
    } else {
        printf("����ʧ��\n");
    }
}

void failedStudent() { //ͳ�Ƴ����Ʋ������ѧ����Ϣ�ͳɼ�

    if(studentLength(first) == 0) {
        printf("û��ѧ��\n\n");
        return;
    }


    printf("1.��ѧ\n");
    printf("2.Ӣ��\n");
    getchar();
    char m = getchar();
    if(m=='1') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(s->record->math < 60) {
                printf("������%s,��ѧ��%.2f,���ģ�%.2f\n",s->name,s->record->math,s->record->english);
            }
        }
    } else if(m == '2') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(s->record->english < 60) {
                printf("������%s,��ѧ��%.2f,���ģ�%.2f\n",s->name,s->record->math,s->record->english);
            }
        }
    }
}

void avgStudent() { //��Ůƽ����

    if(studentLength(first) == 0) {
        printf("û��ѧ��\n\n");
        return;
    }


    printf("1����\n");
    printf("2��Ů\n");

    float count = 0,num = 0;

    char m = getchar();
    if(m == '1') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(strcmp(s->gender,"��")) {
                count+=s->record->count;
                ++num;
            }
        }
    } else if(m=='2') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(strcmp(s->gender,"Ů")) {
                count+=s->record->count;
                ++num;
            }
        }
    }


    printf("ƽ���֣�%.2f",count / num);
}

Student * getStudent(Student * head,int index) { //���������õ�ѧ��
    int len = studentLength(head);
    if(len <= index) return NULL;

    Student * temp = head;
    for(int i = 0; i < len; i ++) {
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

        int len = studentLength(first);

        for(int i = 0; i < len;i++) {
            Student * sorting = getStudent(first,i);
            for (int j = i+1; j < len; j ++) {
                Student * temp = getStudent(first,j);

                if(sorting->record->count < temp->record->count) {
                    Student * swap = (Student*) malloc(sizeof(Student));
                    swap->name = sorting->name;
                    swap->no=sorting->no;
                    swap->gender=sorting->gender;
                    swap->record=sorting->record;


                    sorting->no = temp->no;
                    sorting->name = temp->name;
                    sorting->gender=temp->gender;
                    sorting->record=temp->record;

                    temp->no = swap->no;
                    temp->name = swap->name;
                    temp->gender = swap->gender;
                    temp->record = swap->record;
                }
            }
        }

    } else if(m=='2') {
        printf("1.��ѧ\n");
        printf("2.Ӣ��\n");

        m = getchar();
        if(m == '1') {

            int len = studentLength(first);

            for(int i = 0; i < len;i++) {
                Student * sorting = getStudent(first,i);
                for (int j = i+1; j < len; j ++) {
                    Student * temp = getStudent(first,j);

                    if(sorting->record->math < temp->record->math) {
                        Student * swap = (Student*) malloc(sizeof(Student));
                        swap->name = sorting->name;
                        swap->no=sorting->no;
                        swap->gender=sorting->gender;
                        swap->record=sorting->record;


                        sorting->no = temp->no;
                        sorting->name = temp->name;
                        sorting->gender=temp->gender;
                        sorting->record=temp->record;

                        temp->no = swap->no;
                        temp->name = swap->name;
                        temp->gender = swap->gender;
                        temp->record = swap->record;
                    }
                }
            }
        } else {

            int len = studentLength(first);

            for(int i = 0; i < len;i++) {
                Student * sorting = getStudent(first,i);
                for (int j = i+1; j < len; j ++) {
                    Student * temp = getStudent(first,j);

                    if(sorting->record->english < temp->record->english) {
                        Student * swap = (Student*) malloc(sizeof(Student));
                        swap->name = sorting->name;
                        swap->no=sorting->no;
                        swap->gender=sorting->gender;
                        swap->record=sorting->record;


                        sorting->no = temp->no;
                        sorting->name = temp->name;
                        sorting->gender=temp->gender;
                        sorting->record=temp->record;

                        temp->no = swap->no;
                        temp->name = swap->name;
                        temp->gender = swap->gender;
                        temp->record = swap->record;
                    }
                }
            }
        }
    }
    printf("�������\n\n");
}


char no[20];
char * getStudentNo() {
    printf("������ѧ��:");

    scanf("%s",&no[0]);

    return &no[0];

}

void updateStudent() {
    char * no = getStudentNo();

    Student * temp = first;
    for(int i = 0; i < studentLength(first); i++) {
        if(strcmp(temp->no,no) == 0) {
            printf("ѧ�ţ�");
            scanf("%s",&temp->no[0]);

            printf("������");
            scanf("%s",&temp->name[0]);

            printf("�Ա�");
            scanf("%s",&temp->gender[0]);

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


int studentLength(Student * head) {
    if (head == NULL)
        return 0;

    int len = 1;

    Student * temp = head;
    while (1) {

        if (temp->next == NULL) {
            return len;
        } else {
            temp = temp->next;
        }
        ++len;
    }
}

void insertStudentLinked(Student * s) {
    Student * lastStudent =  getStudentLastNode();
    if(lastStudent == NULL) first = s;
    else lastStudent->next = s;
}

Student * getStudentLastNodeByHead(Student * head) {
    if(head == NULL) return NULL;

    Student * temp = head;
    while(temp->next!=NULL) {
        temp = temp->next;
    }
    return temp;
}

Student * getStudentLastNode() {
    if(first == NULL) return NULL;

    Student * temp = first;
    while(1) {
        if(temp->next==NULL) {
            return temp;
        } else {
            temp = temp->next;
        }
    }
}


void addStudent() {
    Student * newStudent = (Student *) malloc(sizeof(Student));
    newStudent->next = NULL;
    newStudent->parent = NULL;
    newStudent->record = (Record *) malloc(sizeof(Record));


    if(first != NULL) {
        Student * last = getStudentLastNode();
        newStudent->parent = last;
    }


    printf("ѧ�ţ�");
    char * no = (char*) malloc(sizeof(char)*20);
    scanf("%s",no);
    newStudent->no = no;

    printf("������");
    char * name = (char*) malloc(sizeof(char)*20);
    scanf("%s",name);
    newStudent->name = name;

    printf("�Ա�");
    char * gender = (char*) malloc(sizeof(char)*20);
    scanf("%s",gender);
    newStudent->gender = gender;

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
    for(int i = 0; i < studentLength(first); i++) {
        if(strcmp(temp->no,no) == 0) {
            temp->parent = temp->next;
            printf("ɾ��%s�ɹ�\n\n",no);
            return;
        }
    }

    printf("ɾ��%sʧ�ܣ�û�����ѧ��\n\n",no);
}
