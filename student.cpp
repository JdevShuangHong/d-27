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
    char * no;
    char * name;
    char * gender;
    Record * record;
    Student * next;
    Student * parent;
} Student;

Student * first = NULL; //第一个学生

void addStudent(); //添加学生

void deleteStudent(); //删除学生

void updateStudent(); //更新学生

void sortStudent(); //排名学生

void avgStudent(); //统计平均分

void failedStudent(); //不及格的学生

void saveStudent(Student * head); //保存学生

void sortFileStudent(); //排序已经存在的学生

void insertStudentLinked(Student * s); //插入链表

Student * getStudentLastNode();//得到学生最后一个节点

int studentLength(Student * head); //计算有多少个学生

char * getStudentNo(); //从用户输入得到学生的学号

Student * getStudent(Student * head,int index); //根据索引得到学生

Student * getStudentLastNodeByHead(Student * head);

void sortByCount(Student * head); //通过总分拍寻

char **split(char sep, const char *str, int *size); //返回一个 char *arr[], size为返回数组的长度

void queryMark();

void queryHigh(Student *pStudent);


const  char * cjfile = "d:/chengji.txt";

int main(int argc, char const *argv[])
{
    FILE * file = fopen(cjfile,"rw");
    if(file == NULL) {
        printf("读取失败\n");
    } else {
        char StrLine[1024];
        int size;

        while (!feof(file)) {
            fgets(StrLine, 1024, file);  //读取一行
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
        //关闭文件
        fclose(file);
    }

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
    } else if(m == '2') {   // 学生选项
        Student * login;
        printf("1.请输入你的学号：");
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
            printf("没有这个学生");
            return 0;
        }

        while(1) {

            printf("1：按照学号或姓名查询学生成绩\n");
            printf("2：统计出总分或单科比自己分数高的学生信息和成绩\n");

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

void queryHigh(Student *login) { //查询更高的
    getchar();

    int len = studentLength(first);
    char data[20];

    printf("1.单科查询.\n");
    printf("2.总分\n");
    int m = getchar();

    if(m=='1') {
        printf("1.数学\n");
        printf("2.英语\n");
        getchar();
        m=getchar();
        if(m == '1') {
            int len = studentLength(first);
            for(int i = 0; i < len;i++) {
                Student *s = getStudent(first, i);
                if(s->record->math > login->record->math) {
                    printf("学号：%s,姓名：%s,性别：%s,数学：%f,英语：%f,总分：%f\n",s->no,s->name,s->gender,
                           s->record->math,s->record->english,s->record->count);
                }
            }
        } else if(m='2') {
            int len = studentLength(first);
            for(int i = 0; i < len;i++) {
                Student *s = getStudent(first, i);
                if(s->record->english > login->record->english) {
                    printf("学号：%s,姓名：%s,性别：%s,数学：%f,英语：%f,总分：%f\n",s->no,s->name,s->gender,
                           s->record->math,s->record->english,s->record->count);
                }
            }
        }


    } else if(m=='2') { //总分
        int len = studentLength(first);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(s->record->count > login->record->count) {
                printf("学号：%s,姓名：%s,性别：%s,数学：%f,英语：%f,总分：%f\n",s->no,s->name,s->gender,
                       s->record->math,s->record->english,s->record->count);
            }
        }
    }
}

void queryMark() { //查询分数
    getchar();

    int len = studentLength(first);
    char data[20];

    printf("1.学号\n");
    printf("2.姓名\n");
    int m = getchar();

    if(m=='1') {
        printf("请输入学号：");
        scanf("%s",data);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(strcmp(s->no,data)==0) {
                printf("数学：%f,英语：%f,总分：%f\n",s->record->math,s->record->english,s->record->count);
                return;
            }
        }
    } else if(m=='2') {
        printf("请输入学号：");
        scanf("%s",data);
        for(int i = 0; i < len;i++) {
            Student *s = getStudent(first, i);
            if(strcmp(s->name,data)==0) {
                printf("数学：%f,英语：%f,总分：%f\n",s->record->math,s->record->english,s->record->count);
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

void sortFileStudent() { //对文件中的学生排序
    FILE * file = fopen(cjfile,"rw");
    if(file == NULL) {
        printf("读取失败\n");
    } else {
        char StrLine[1024];
        int size;

        Student * head = NULL;
        while (!feof(file))
        {
            fgets(StrLine, 1024, file);  //读取一行
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

        //关闭文件
        fclose(file);

        sortByCount(head);

        saveStudent(head);
    }
}


//返回一个 char *arr[], size为返回数组的长度
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
            ret[j] = (char*)calloc(i - lastindex, sizeof(char)); //分配子串长度+1的内存空间
            memcpy(ret[j], str + lastindex + 1, i - lastindex - 1);
            j++;
            lastindex = i;
        }
    }
    //处理最后一个子串
    if (lastindex <= strlen(str) - 1)
    {
        ret[j] = (char*)calloc(strlen(str) - lastindex, sizeof(char));
        memcpy(ret[j], str + lastindex + 1, strlen(str) - 1 - lastindex);
        j++;
    }

    *size = j;

    return ret;
}


void saveStudent(Student * head) { //保存学生

    if(studentLength(head) == 0) {
        printf("没有学生\n\n");
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

        printf("保存成功\n");
    } else {
        printf("保存失败\n");
    }
}

void failedStudent() { //统计出单科不及格的学生信息和成绩

    if(studentLength(first) == 0) {
        printf("没有学生\n\n");
        return;
    }


    printf("1.数学\n");
    printf("2.英语\n");
    getchar();
    char m = getchar();
    if(m=='1') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(s->record->math < 60) {
                printf("姓名：%s,数学：%.2f,语文：%.2f\n",s->name,s->record->math,s->record->english);
            }
        }
    } else if(m == '2') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(s->record->english < 60) {
                printf("姓名：%s,数学：%.2f,语文：%.2f\n",s->name,s->record->math,s->record->english);
            }
        }
    }
}

void avgStudent() { //男女平均分

    if(studentLength(first) == 0) {
        printf("没有学生\n\n");
        return;
    }


    printf("1：男\n");
    printf("2：女\n");

    float count = 0,num = 0;

    char m = getchar();
    if(m == '1') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(strcmp(s->gender,"男")) {
                count+=s->record->count;
                ++num;
            }
        }
    } else if(m=='2') {
        for (int i = 0; i < studentLength(first); i++) {
            Student * s = getStudent(first,i);
            if(strcmp(s->gender,"女")) {
                count+=s->record->count;
                ++num;
            }
        }
    }


    printf("平均分：%.2f",count / num);
}

Student * getStudent(Student * head,int index) { //根据索引得到学生
    int len = studentLength(head);
    if(len <= index) return NULL;

    Student * temp = head;
    for(int i = 0; i < len; i ++) {
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
        printf("1.数学\n");
        printf("2.英语\n");

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
    printf("排序完成\n\n");
}


char no[20];
char * getStudentNo() {
    printf("请输入学号:");

    scanf("%s",&no[0]);

    return &no[0];

}

void updateStudent() {
    char * no = getStudentNo();

    Student * temp = first;
    for(int i = 0; i < studentLength(first); i++) {
        if(strcmp(temp->no,no) == 0) {
            printf("学号：");
            scanf("%s",&temp->no[0]);

            printf("姓名：");
            scanf("%s",&temp->name[0]);

            printf("性别：");
            scanf("%s",&temp->gender[0]);

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


    printf("学号：");
    char * no = (char*) malloc(sizeof(char)*20);
    scanf("%s",no);
    newStudent->no = no;

    printf("姓名：");
    char * name = (char*) malloc(sizeof(char)*20);
    scanf("%s",name);
    newStudent->name = name;

    printf("性别：");
    char * gender = (char*) malloc(sizeof(char)*20);
    scanf("%s",gender);
    newStudent->gender = gender;

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
    for(int i = 0; i < studentLength(first); i++) {
        if(strcmp(temp->no,no) == 0) {
            temp->parent = temp->next;
            printf("删除%s成功\n\n",no);
            return;
        }
    }

    printf("删除%s失败，没有这个学生\n\n",no);
}
