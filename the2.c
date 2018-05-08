#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
int Molecule_count = 0;
void print_matrix(int **ls_num,int **rs_num)
{
    int k ;
    int i ;
    printf("\n -------------------- \n");
    k = 0;
    i = 0;
    while(k < Molecule_count)
    {
        i = 0;
        while(ls_num[i] != NULL)
        {
            printf("%d ",ls_num[i][k]);
            i++;
        }
        i = 0;
        while(rs_num[i] != NULL)
        {
            printf("%d ",rs_num[i][k]);
            i++;
        }
        printf("\n");
        k++;
    }
    printf("\n -------------------- \n");
}
int powerof(int base,int ex)
{
    int res;
    res = 1;
    while(ex)
    {
        res *= base;
        ex--;
    }
    return res;
}
/*Stack operations*/
int pop_stack(int* stack)
{
    int tmp;
    if(stack[0] == 0)
    {
        return 1;
    }
    tmp = stack[stack[0]];
    stack[stack[0]] = -1;
    stack[0] = stack[0]-1;
    return tmp;
}
int top_stack(int* stack)
{
    int i;
    int res;
    res = 1;
    i  = stack[0];
    if(i == 0)
    {
        return res;
    }
    while(i > 0)
    {
        res *= stack[i];
        i--;
    }
    return res;
}
void push_stack(int* stack,int new_int)
{
    stack[0] = stack[0] + 1;
    stack[stack[0]] = new_int;
}
void copy_matrix(int** m1, int** m2,int** n1, int** n2)
{
    int i ;
    int k ;
    i = 0;
    k = 0;
    while(m1[i])
    {
        k = 0;
        while(k < Molecule_count)
        {
            n1[i][k] = m1[i][k];
            k++;
        }
        i++;
    }
    i = 0;
    while(m2[i])
    {
        k = 0;
        while(k < Molecule_count)
        {
            n2[i][k] = m2[i][k];
            k++;
        }
        i++;
    }
}
/*Matrix operations

 Created by Monata on 5/6/2018.
*/
#include <stdio.h>
int gcd(int num1,int num2)
{
    int tmp;

    if(num1 < 0)
    {
        num1 = num1*(-1);
    }
    if(num2 < 0)
    {
        num2 = num2*(-1);
    }
    while(num2 != 0)
    {
        tmp = num1%num2;
        num1 = num2;
        num2 = tmp;
    }
    return num1;
}
int lcm(int num1,int num2)
{
    int tmp;
    tmp = gcd(num1,num2);
    num1 /= tmp;
    num2 /= tmp;
    return (num1 * num2 * tmp);
}
void line_multiply(int **m1,int** m2,int c,int line)
{
    int i;
    i = 0;
    while(m1[i] != NULL)
    {
        m1[i][line] *= c;
        i++;
    }
    i = 0;
    while(m2[i] != NULL)
    {
        m2[i][line] *= c;
        i++;
    }
}
void line_divide(int **m1,int** m2,int c,int line)
{
    int i;
    i= 0;
    while(m1[i] != NULL)
    {
        m1[i][line] /= c;
        i++;
    }
    i = 0;
    while(m2[i] != NULL)
    {
        m2[i][line] /= c;
        i++;
    }
}
void line_substract(int **m1,int** m2,int line1, int line2)
{
    int i;
    i= 0;
    while(m1[i] != NULL)
    {
        m1[i][line2] += (-1)*(m1[i][line1]);
        i++;
    }
    i = 0;
    while(m2[i] != NULL)
    {
        m2[i][line2] += (-1)*(m2[i][line1]);
        i++;
    }
}
void line_add(int **m1,int** m2,int line1, int line2)
{
    int i;
    i= 0;
    while(m1[i] != NULL )
    {
        m1[i][line2] += (m1[i][line1]);
        i++;
    }
    i = 0;
    while(m2[i] != NULL)
    {
        m2[i][line2] += (m2[i][line1]);
        i++;
    }
}
void no_zero(int**m1,int**m2)
{
    int i;
    int k;
    i = 0;
    k = 0;
    while(m1[i] != NULL)
    {
        k = i+1;
        while (k < Molecule_count)
        {
            line_add(m1, m2, i, k);
            k++;
        }
        i++;
    }
}
void matrix_echelon(int** m1,int** m2)
{
    int ** crnt;
    int tmp;
    int i;
    int k;
    int tempi;
    int old_i;
    crnt = m1;
    tmp = 1;
    i = 0;
    k = 0;
    tempi = 0;
    no_zero(m1,m2);
    while(crnt[i] != NULL)
    {
        k = i+1;

        while(k < Molecule_count)
        {
            if(crnt[i][i] == 0)
            {
                tempi = (i+1);
                while(crnt[i][i] == 0)
                {
                    if(tempi < Molecule_count)
                    {
                        line_add(m1, m2, tempi, i);
                        tempi++;
                    }
                    else
                    {
                        k++;
                        break;
                    }
                }
                continue;
            }
            if(crnt[i][k] == 0)
            {
                k++;
                continue;
            }
            if(crnt[i][i] > crnt[i][k])
            {
                tmp = lcm(crnt[i][i],crnt[i][k]);
                line_multiply(m1,m2,(tmp/crnt[i][k]),k);
                line_multiply(m1,m2,(tmp/crnt[i][i]),i);
                line_substract(m1,m2,i,k);
            }
            else if(crnt[i][i] < crnt[i][k])
            {
                tmp = lcm(crnt[i][i],crnt[i][k]);
                line_multiply(m1,m2,(tmp/crnt[i][k]),k);
                line_multiply(m1,m2,(tmp/crnt[i][i]),i);
                line_substract(m1,m2,i,k);
            }
            else
            {
                line_substract(m1,m2,i,k);
            }
            k++;
        }
        i++;
    }
    old_i = i;
    i = 0;
    crnt = m2;

    while(crnt[i+1] != NULL)
    {
        k = old_i+1;

        while(k < Molecule_count)
        {
            if(crnt[i][old_i] == 0)
            {
                tempi = (old_i+1);
                while(crnt[i][old_i] == 0)
                {
                    if(tempi < Molecule_count)
                    {
                        line_add(m1, m2, tempi, old_i);
                        tempi++;
                    }
                    else
                    {
                        k++;
                        break;
                    }
                }
                continue;
            }
            if(crnt[i][k] == 0)
            {
                k++;
                continue;
            }
            if(crnt[i][old_i] > crnt[i][k])
            {
                tmp = lcm(crnt[i][old_i],crnt[i][k]);
                line_multiply(m1,m2,(tmp/crnt[i][k]),k);
                line_multiply(m1,m2,(tmp/crnt[i][old_i]),old_i);
                line_substract(m1,m2,i,k);
            }
            else if(crnt[i][old_i] < crnt[i][k])
            {
                tmp = lcm(crnt[i][old_i],crnt[i][k]);
                line_multiply(m1,m2,(tmp/crnt[i][k]),k);
                line_multiply(m1,m2,(tmp/crnt[i][old_i]),old_i);
                line_substract(m1,m2,old_i,k);
            }
            k++;
        }
        i++;
        old_i++;
    }
}
void montante (int **m1,int**m2,int**n1,int**n2,int i , int j , int p,int p_i, int p_j) {
    int l;
    l = 0;
    while (m1[l] != NULL) {
        l++;
    }
    if (i < l)
    {
        if(p_i < l)
        {
            m1[i][j] = (((n1[p_i][p_j])*(n1[i][j])) - (n1[i][p_j]*n1[p_i][j]))/p;
        }
        else
        {
            p_i = (p_i -l);
            m1[i][j] = (((n2[p_i][p_j])*(n1[i][j])) - (n1[i][p_j]*n2[p_i][j]))/p;
        }
    }
    else
    {
        i = (i-l);
        if(p_i < l)
        {
            m2[i][j] = (((n1[p_i][p_j])*(n2[i][j])) - (n2[i][p_j]*n1[p_i][j]))/p;
        }
        else
        {
            p_i = (p_i -l);
            m2[i][j] = (((n2[p_i][p_j])*(n2[i][j])) - (n2[i][p_j]*n2[p_i][j]))/p;
        }
    }
}
int getp(int** m1,int** m2,int j)
{
    int i;
    int l;
    l = 0;
    i = 0;
    while(m1[i] != NULL)
    {
        if(m1[i][j] != 0)
        {
            return i;
        }
        i++;
    }
    l = i;
    i = 0;
    while(m2[i] != NULL)
    {
        if(m2[i][j] != 0)
        {
            return (i+l);
        }
        i++;
    }
    return 0;
}
void no_overflow(int **m1, int** m2)
{
    int k;
    int i;
    int gd;
    k = 0;
    i = 0;
    while(k < Molecule_count)
    {
        i = 0;
        gd = m1[i][k];

        while (m1[i] != NULL)
        {
            gd = gcd(gd, m1[i][k]);
            i++;
        }
        i = 0;
        while (m2[i] != NULL)
        {
            gd = gcd(gd, m2[i][k]);
            i++;
        }
        if(gd == 0)
        {
            gd = 1;
        }
        line_divide(m1, m2, gd, k);
        k++;
    }
}

/*Indexing and Construction of matrices*/
int addindex(char** array,char Atom_char_1,char Atom_char_2,int* Molecule_count)
{
    int i;
    i = 0;
    if(Atom_char_2 > 96 && Atom_char_2 < 123)
    {
        while (array[i])
        {
            if (array[i][0] == Atom_char_1 && array[i][1] == Atom_char_2)
            {
                return i;
            }
            i++;
        }
        array[i] = malloc(sizeof(char) * 3);
        array[i][0] = Atom_char_1;
        array[i][1] = Atom_char_2;
        array[i][2] = '\0';
        array[i+1] = NULL;
        (*Molecule_count)++;
        return 0;
    }
    else
    {
        while (array[i])
        {
            if (array[i][0] == Atom_char_1)
            {
                return i;
            }
            i++;
        }
        array[i] = malloc(sizeof(char) * 2);
        array[i][0] = Atom_char_1;
        array[i][1] = '\0';
        array[i+1] = NULL;
        (*Molecule_count)++;
        return 0;
    }
}
int add_to_array(int * array,char *molecule,int last_index,int* multiplier_stack,char ** index_get_array)
{
    int multiplier;
    int temp_mult;
    int i;
    int k;
    temp_mult = 0;
    i = 0;
    k = 0;
    multiplier = top_stack(multiplier_stack);
    if(last_index == -17)
    {
        while(molecule[i])
        {
            i++;
        }
        last_index = (i-1);
    }
    if(last_index < 0)
    {
        return 0;
    }
    if(molecule[last_index] > 64 && molecule[last_index] < 91)/*if uppercase*/
    {
        if(last_index > 0)
        {
            if(molecule[last_index-1] > 64 && molecule[last_index-1] < 91)
            {
                array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
            }
            else if(molecule[last_index-1] > 96 && molecule[last_index-1] < 123)
            {
                array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                return add_to_array(array,molecule,last_index-2,multiplier_stack,index_get_array);
            }
            else
            {
                array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
            }
        }
        else
        {
            array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
            return 0;
        }
    }
    else if(molecule[last_index] > 96 && molecule[last_index] < 123)
    {
        array[addindex(index_get_array,molecule[last_index-1],molecule[last_index],&Molecule_count)] += multiplier;
        return add_to_array(array,molecule,last_index-2,multiplier_stack,index_get_array);
    }
    else if(molecule[last_index] > 47 && molecule[last_index] < 58) /*if integer*/
    {
        while(molecule[last_index] > 47 && molecule[last_index] < 58) /*for if the int is bigger than 9*/
        {
            temp_mult += ((molecule[last_index]-48) * powerof(10,k));
            last_index--;
            k++;
        }
        if(molecule[last_index] == ')')
        {
            push_stack(multiplier_stack,(temp_mult));
            return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
        }
        multiplier *= temp_mult;
        if(molecule[last_index] > 64 && molecule[last_index] < 91)
        {
            if(last_index > 0)
            {
                if(molecule[last_index-1] > 64 && molecule[last_index-1] < 91)
                {
                    array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                    return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
                }
                else if(molecule[last_index-1] > 96 && molecule[last_index-1] < 123)
                {
                    array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                    return add_to_array(array,molecule,last_index-2,multiplier_stack,index_get_array);
                }
                else
                {
                    array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                    return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
                }
            }
            else
            {
                array[addindex(index_get_array,molecule[last_index],'\0',&Molecule_count)] += multiplier;
                return 0;
            }
        }
        else if(molecule[last_index] > 96 && molecule[last_index] < 123)
        {
            array[addindex(index_get_array,molecule[last_index-1],molecule[last_index],&Molecule_count)] += multiplier;
            return add_to_array(array,molecule,last_index-2,multiplier_stack,index_get_array);
        }
    }
    else if(molecule[last_index] == '(')
    {
        pop_stack(multiplier_stack);
        return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
    }
    else
    {

        return add_to_array(array,molecule,last_index-1,multiplier_stack,index_get_array);
    }
    return 0;
}
int main() {
    int i = 0;
    int k = 0;
    int j = 0;
    int p = 1;
    int l = 0;
    int f = 0;
    int o = 0;
    int ls_index = 0;
    int rs_index = 0;
    int word_index = 0;
    int ** ls_num = NULL;
    int ** ls_new = NULL;
    int ** rs_num = NULL;
    int ** rs_new = NULL;
    int * multiplier_stack ;
    int * result_stack ;
    char c = '1';
    char Atom_char_1;
    char Atom_char_2;
    char ** index_get_array;
    char ** ls;
    char ** rs;
    i = 0;
    k = 0;
    j = 0;
    p = 1;
    l = 0;
    f = 0;
    o = 0;
    ls_index = 0;
    rs_index = 0;
    word_index = 0;
    ls_num = NULL;
    rs_num = NULL;
    rs_new = NULL;
    ls_new = NULL;
    multiplier_stack = calloc(sizeof(int),100);
    c = '1';
    index_get_array = malloc(sizeof(char*) * 100);
    ls = malloc(sizeof(char*) * 400);
    rs = malloc(sizeof(char*) * 400);
    index_get_array[0] = NULL;
    multiplier_stack[1] = -1;
    /*assign left side*/
    rs[rs_index] = malloc(1);
    ls[ls_index] = malloc(1);
    scanf("%c",&c);
    Atom_char_2 = c;
    Atom_char_1 = ' ';
    while(c != '-')
    {
        if(Atom_char_1 > 64 && Atom_char_1 < 91)
        {
            addindex(index_get_array,Atom_char_1,Atom_char_2,&Molecule_count);
        }
        if(c == '+')
        {
            scanf("%c",&c);
            ls[ls_index] = realloc(ls[ls_index], sizeof(char) * (word_index+2));
            ls[ls_index][word_index] = '\0';
            ls_index++;
            ls[ls_index] = malloc(1);
            word_index = 0;
            continue;
        }
        ls[ls_index] = realloc(ls[ls_index], sizeof(char) * (word_index+1));
        ls[ls_index][word_index] = c;
        word_index++;
        scanf("%c",&c);
        Atom_char_1 = Atom_char_2;
        Atom_char_2 = c;
    }
    ls[ls_index] = realloc(ls[ls_index], sizeof(char) * (word_index+1));
    ls[ls_index][word_index] = '\0';
    ls[ls_index+1] = NULL;
    scanf("%c",&c);
    scanf("%c",&c);

    /*assign right side*/
    word_index = 0;
    while(c != '\n')
    {
        if(Atom_char_1 > 64 && Atom_char_1 < 91)
        {
            addindex(index_get_array,Atom_char_1,Atom_char_2,&Molecule_count);
        }
        if(c == '+')
        {
            scanf("%c",&c);
            rs[rs_index] = realloc(rs[rs_index], sizeof(char) * (word_index+2));
            rs[rs_index][word_index] = '\0';
            rs_index++;
            rs[rs_index] = malloc(1);
            word_index = 0;
            continue;
        }
        rs[rs_index] = realloc(rs[rs_index], sizeof(char) * (word_index+1));
        rs[rs_index][word_index] = c;
        word_index++;
        scanf("%c",&c);
        Atom_char_1 = Atom_char_2;
        Atom_char_2 = c;
    }
    rs[rs_index] = realloc(rs[rs_index], sizeof(char) * (word_index+1));
    rs[rs_index][word_index] = '\0';
    rs[rs_index+1] = NULL;

/*call numindexes*/
    /*for left*/
    i = 0;
    ls_num = malloc(sizeof(char*) * (ls_index+1));
    ls_new = malloc(sizeof(char*) * (ls_index+1));
    while(ls[i])
    {
        ls_num[i] = calloc(sizeof(int), Molecule_count);
        ls_new[i] = calloc(sizeof(int), Molecule_count);
        add_to_array(ls_num[i],ls[i],-17,multiplier_stack,index_get_array);
        i++;
    }
    ls_num[i] = NULL;
    ls_new[i] = NULL;
    i = 0;

    /*for right*/
    i = 0;
    rs_num = malloc(sizeof(char*) * (ls_index+10));
    rs_new = malloc(sizeof(char*) * (ls_index+10));
    while(rs[i])
    {
        rs_num[i] = calloc(sizeof(int), Molecule_count);
        rs_new[i] = calloc(sizeof(int), Molecule_count);
        add_to_array(rs_num[i],rs[i],-17,multiplier_stack,index_get_array);
        i++;
    }
    rs_num[i] = NULL;
    rs_new[i] = NULL;


    /*tests*/
    i = 0;
    k = 0;
    j = 0;
    l = 0;
    f = 0;
    while (ls_num[l] != NULL) {
        l++;
    }
    while (rs_num[f] != NULL) {
        f++;
    }
    matrix_echelon(ls_num,rs_num);
    no_overflow(ls_num,rs_num);
    p = 1;
    o = 0;
    copy_matrix(ls_num,rs_num,ls_new,rs_new);
    while(j < (l+f-1))
    {
        i = 0;
        while(i < (l+f))
        {
            k = 0;
            while(k < Molecule_count)
            {

                if(k == o)
                {
                    k++;
                    continue;
                }
                montante(ls_num,rs_num,ls_new,rs_new,i,k,p,j,o);
                k++;
            }
            i++;
        }
        if(j < l)
        {
            p = ls_num[j][o];
        }
        else
        {
            p = rs_num[j-l][o];
        }
        j++;
        o = getp(ls_num,rs_num,j);
        copy_matrix(ls_num,rs_num,ls_new,rs_new);
    }
    print_matrix(ls_num,rs_num);
    i = 0;
    o = 2000000000;
    f--;
    Molecule_count = (l+f);
    result_stack = malloc(40 * sizeof(int));
    while(i < Molecule_count)
    {
        o = abs(rs_num[f][i]);
        o = gcd(ls_num[0][0],o);
        o = abs((ls_num[0][0] / o));
        result_stack[i] = o;
        i++;
    }
    o = 1;
    result_stack[i] = -1;
    i = 0;
    while(result_stack[i] != -1)
    {
        o = lcm(result_stack[i],o);
        i++;
    }
    i=0;
    p = o;
    while(i < Molecule_count)
    {
        printf("%d %d \n",i,o);
        rs_num[f][i] *= o;
        i++;
    }
    o = ls_num[0][0];
    i = 0;
    print_matrix(ls_num,rs_num);

    while(i < Molecule_count)
    {
        printf("%d ",abs(rs_num[f][i]/o));
        i++;
    }
    printf("%d",abs(p));
    return 0;
}
