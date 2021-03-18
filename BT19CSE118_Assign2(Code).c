#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 500//1024 bits means nearly no of 309 digits

void add(char a[], char b[], int flag);

void strRev(char a[])
{
    int n = strlen(a);
    for(int i = 0; i < n/2; ++i)
    {
        char temp = a[i];
        a[i] = a[n - i - 1];
        a[n - i - 1] = temp;
    }
}

void curtail_zeroes(char a[])
{
    int n = strspn(a, "0");
    char s[500];
    int j = 0;
    for(int i = n; a[i] != '\0'; ++i)
    {
        s[j++] = a[i];
    }
    s[j] = '\0';
    strcpy(a, s);
}

void multiply(char str1[], char str2[])
{
    int flag = 1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if(len1 + len2 > 310)
    {
        printf("Overflow\n");
        return;
    }
    if((len1 == 1 && str1[0] == '0') || (len2 == 1 && str2[0] == '0'))
    {
        printf("0\n");
        return;
    }
    else
    {
        if(str1[0] == '-' && str2[0] == '-')
        {
            str1[0] = '0';
            str2[0] = '0';
            flag = 1;
        }
        else if(str1[0] == '-')
        {
            str1[0] = '0';
            flag = 0;
        }
        else if(str2[0] == '-')
        {
            str2[0] = '0';
            flag = 0;
        }
        curtail_zeroes (str1);
        curtail_zeroes (str2);
        len1 = strlen(str1);
        len2 = strlen(str2);
        int ans[SIZE] = {0};
        for(int i = len1 - 1; i >= 0; i--)
        {
            for(int j = len2 - 1; j >= 0; j--)
            {
                ans[i+j+1]+=(str1[i]-'0')*(str2[j]-'0');
                ans[i+j]+=ans[i+j+1]/10;
                ans[i+j+1]%=10;
            }
        }
        int i = 0;
        while(i < len1 + len2 && ans[i] == 0)
            i++;
        char s[SIZE];
        int j = 0;
        while(i < len1 + len2)
        {
            s[j++] = ans[i++] + '0';
        }
        s[j] = '\0';
        curtail_zeroes (s);
        if(strlen(s)  == 0)
        {
            printf("0\n");
            return;
        }
        printf("Answer is: \n");
        if(flag == 0)
            printf("-");
        printf("%s\n", s);
        return;
    }
    return;
}

int isSmaller(char str1[], char str2[])
{
    // Calculate lengths of both string
    int n1 = strlen(str1), n2 = strlen(str2);
    if(n1 < n2)
        return 1;
    if(n2 < n1)
        return 0;
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return 1;
        else if (str1[i] > str2[i])
            return 0;

    return 0;
}

void findDiff(char str1[], char str2[])
{
    int flag = 0;
    if(str2[0] == '-' && str1[0] != '-')
    {
        str2[0] = '0';
        curtail_zeroes (str2);
        add(str1, str2, 0);
    }
    else if(str1[0] == '-' && str2[0] != '-')
    {
        str1[0] = '0';
        curtail_zeroes (str1);
        add(str1, str2, 1);
    }
    else
    {
        if(str1[0] == '-' && str2[0] == '-')
        {
            str1[0] = '0';
            str2[0] = '0';
            curtail_zeroes (str1);
            curtail_zeroes (str2);
            findDiff(str2, str1);
        }
        else
        {
            if (isSmaller(str1, str2))
            {
                char temp[SIZE];
                strcpy(temp, str1);
                strcpy(str1, str2);
                strcpy(str2, temp);
                flag = 1;
            }
            char str[SIZE] = "";
            int n1 = strlen(str1), n2 = strlen(str2);
            strRev(str1);
            strRev(str2);
            int carry = 0;
            int k = 0;
            // Run loop till small string length
            // and subtract digit of str1 to str2
            for (int i = 0; i < n2; i++)
            {
                int sub = ((str1[i] - '0') - (str2[i] - '0') - carry);
                if (sub < 0)
                {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                    carry = 0;
                str[k++] = sub + '0';
                if(k > 310)
                {
                    printf("Overflow\n");
                    return ;
                }
            }

            // subtract remaining digits of larger number
            for (int i = n2; i < n1; i++)
            {
                int sub = ((str1[i] - '0') - carry);

                // if the sub value is -ve, then make it positive
                if (sub < 0)
                {
                    sub = sub + 10;
                    carry = 1;
                }
                else
                carry = 0;
                str[k++] = sub + '0';
                if(k > 310)
                {
                    printf("Overflow\n");
                    return ;
                }
            }
            str[k] = '\0';
            // reverse resultant string
            strRev(str);
            curtail_zeroes (str);
            printf("Answer is: \n");
            if(flag == 1)
                printf("-");
            printf("%s\n", str);
        }
    }
}

void add(char a[], char b[], int flag)
{
    int limitm = 0, limitn = 0;
    if(a[0] == '-' && b[0] == '-')
    {
        limitm = 1;
        limitn = 1;
    }
    else if(a[0] == '-')
    {
        a[0] = '0';
        curtail_zeroes (a);
        return findDiff(b, a);
    }
    else if(b[0] == '-')
    {
        b[0] = '0';
        curtail_zeroes (b);
        return findDiff(a, b);
    }
    int m = strlen(a);
    int n = strlen(b);
    char ans[SIZE];
    int i = 0;
    int carry = 0;
    while(m > limitm && n > limitn)
    {
        int x = a[m - 1] - '0';
        int y = b[n - 1] - '0';
        int val = x + y + carry;
        carry = val / 10;
        val = val % 10;
        char c = val + '0';
        ans[i] = c;
        i++;
        m--;
        n--;
        if(i > 310)
        {
            printf("Overflow\n");
            return ;
        }
    }
    while(m > limitm)
    {
        int x = a[m - 1] - '0';
        int val = x + carry;
        carry = val / 10;
        val = val % 10;
        char c = val + '0';
        ans[i] = c;
        i++;
        m--;
        if(i > 310)
        {
            printf("Overflow\n");
            return ;
        }
    }
    while(n > limitn)
    {
        int x = b[n - 1] - '0';
        int val = x + carry;
        carry = val / 10;
        val = val % 10;
        char c = val + '0';
        ans[i] = c;
        i++;
        n--;
        if(i > 310)
        {
            printf("Overflow\n");
            return ;
        }
    }
    if(carry > 0)
    {
        ans[i] = carry + '0';
        i++;
        if(i > 310)
        {
            printf("Overflow\n");
            return ;
        }
    }
    ans[i] = '\0';
    strRev(ans);
    curtail_zeroes (ans);
    if(strlen(ans) == 0)
    {
        printf("0\n");
        return;
    }
    printf("Answer is: \n");
    if((limitm == 1 && limitn == 1) || (flag == 1))
        printf("-");
    printf("%s\n", ans);
}

int main()
{
    while(1)
    {
        printf("*******************************************************************************\n");
        printf("If you want to\nadd-enter 1\nsubtract-enter 2\nmultiply-enter 3\nexit-enter 4\n");
        int n;
        scanf("%d", &n);
        if(n < 1 || n > 3)
            return 0;
        printf("--------------------------------------------------------------------------------\n");
        char a[SIZE], b[SIZE];
        printf("Enter 1st number\n");
        scanf("%s", a);
        printf("Enter 2nd number\n");
        scanf("%s", b);
        int p = strlen(a);
        int q = strlen(b);
        if(p > 310 || q > 310)
        {
            printf("Overflow\n");
        }
        else
        {
            if(n == 1)
                add(a, b, 0);
            else if(n == 2)
                findDiff(a, b);
            else if(n == 3)
                multiply(a, b);
            else
                return 0;
        }
    }
    return 0;
}
