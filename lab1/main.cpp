#include <iostream>
#include <functional>

using namespace std;


class Num {
private:
    ::int32_t val = 0;

    Num() = default;

public:
    Num(::int32_t v) {
        val = v;
    }

    Num operator+(Num o) const {
        Num ret(0);
        asm("movl %1, %%eax;"
            "movl %2, %%ebx;"
            "add %%eax, %0;"
            "add %%ebx, %0;"
                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

    Num operator-(Num o) const {
        Num ret(0);
        asm("movl %1, %%eax;"
            "movl %2, %%ebx;"
            "sub %%ebx, %%eax;"
            "movl %%eax, %0;"
                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

//    Num operator*(Num o) const {
//        Num ret(0);
//        int k = 0;
//        int l = 0, r = 0;
//        asm("mov $0, %%ecx;"
//
//            "mov %4, %%ax;"
//            "mov %5, %%bx;"
//
//            "cmp $0, %%ax;"
//            "jge btest;"
//            "inc %%ecx;"
//            "neg %%ax;"
//
//            "btest:"
//            "cmp $0, %%bx;"
//            "jge prog;"
//            "inc %%ecx;"
//            "neg %%bx;"
//
//            "prog:"
//            "mul %%bx;"
//
//            "shll $16, %%edx;"
//            "and $0xffff0000, %%edx;"
//            "and $0x0000ffff, %%eax;"
//            "add %%eax, %%edx;"
//
//            "mov %%edx, %2;"
//            "mov %%eax, %3;"
//
//            "cmp $1, %%ecx;"
//            "jne write;"
//            "neg %%edx;"
//
//            "write:"
//            "mov %%ecx, %1;"
//            "add %%edx, %0;"
//
//            : "=m"(ret.val), "+m"(k), "+m"(l), "+m"(r)
//            : "m"(val), "m"(o.val)
//            );
//        cout << l << " " << r << endl;
//        cout << k << endl;
//        return ret;
//    }


    Num operator*(Num o) const {
        Num ret(0);
        asm("mov $0, %%ecx;"

            "mov %1, %%ax;"
            "mov %2, %%bx;"

            "cmp $0, %%ax;"
            "jge btest;"
            "inc %%ecx;"
            "neg %%ax;"

            "btest:"
            "cmp $0, %%bx;"
            "jge prog;"
            "inc %%ecx;"
            "neg %%bx;"

            "prog:"
            "mul %%bx;"

            "shll $16, %%edx;"
            "and $0xffff0000, %%edx;"
            "and $0x0000ffff, %%eax;"
            "add %%eax, %%edx;"

            "cmp $1, %%ecx;"
            "jne write;"
            "neg %%edx;"

            "write:"
            "mov %%edx, %0;"

                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

//    Num operator/ (Num o) const {
//        Num ret(0);
//        asm("mov $0, %%ecx;"
//
//            "mov %1, %%eax;"
//
//            "cmp $0, %%eax;"
//            "jge afteratest;"
//            "inc %%ecx;"
//
//            "afteratest:"
//            "mov %1, %%edx;"
//
//            "cmp $1, %%ecx;"
//            "jne readb:"
//            "neg %%ax;"
//            "neg %%edx;"
//
//            "readb:"
//            "and $0x0000ffff, %%eax;"
//            "shrl $16, %%edx;"
//            "and $0x0000ffff, %%edx;"
//            "mov %2, %%bx;"
//
//            "cmp $0, %%bx;"
//            "jge divp;"
//            "inc %%ecx;"
//            "neg %%ebx;"
//
//            "divp:"
//            "div %%bx;"
//
//            "cmp $1, %%ecx;"
//            "jne writediv;"
//            "neg %%eax;"
//
//            "writediv:"
//            "mov %%ax, %0;"
//                : "=m"(ret.val)
//                : "m"(val), "m"(o.val)
//                );
//        return ret;
//    }

    Num operator/(Num o) const {
        Num ret(0);
        asm(
                "mov $0, %%ecx;"

                "mov %1, %%eax;"
                "mov %%eax, %%edx;"
                "mov %2, %%ebx;"

                "cmp $0, %%eax;"
                "jge skipneg;"
                "inc %%ecx;"
                "neg %%eax;"
                "neg %%edx;"

                "skipneg:"
                "and $0xffff0000, %%edx;"
                "and $0x0000ffff, %%eax;"

                "cmp $0, %%ebx;"
                "jge skipbneg;"
                "inc %%ecx;"
                "neg %%ebx;"

                "skipbneg:"
                "div %%ebx;"

                "cmp $1, %%ecx;"
                "jne writediv;"
                "neg %%eax;"

                "writediv:"
                "mov %%eax, %0;"
                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

    Num operator<<(Num o) const {
        Num ret(0);
        asm("mov %1, %%eax;"
            "mov %2, %%ebx;"
            "shlx %%ebx, %%eax, %%ecx;"
            "mov %%ecx, %0;"
                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

    Num operator>>(Num o) const {
        Num ret(0);
        asm("mov %1, %%eax;"
            "mov %2, %%ebx;"
            "shrx %%ebx, %%eax, %%ecx;"
            "mov %%ecx, %0;"
                : "=m"(ret.val)
                : "m"(val), "m"(o.val)
                );
        return ret;
    }

    bool operator<(Num o) {
        int r;
        asm("mov $0, %%ecx;"
            "mov %1, %%eax;"
            "mov %2, %%ebx;"
            "cmp %%eax, %%ebx;"
            "jle writele;"
            "inc %%ecx;"
            "writele:"
            "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    bool operator>(Num o) {
        int r;
        asm("mov $0, %%ecx;"
            "mov %1, %%eax;"
            "mov %2, %%ebx;"
            "cmp %%eax, %%ebx;"
            "jge writege;"
            "inc %%ecx;"
            "writege:"
            "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    bool operator==(Num o) {
        int r;
        asm("mov $0, %%ecx;"
            "mov %1, %%eax;"
            "mov %2, %%ebx;"
            "cmp %%eax, %%ebx;"
            "jne writeeq;"
            "inc %%ecx;"
            "writeeq:"
            "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    int operator|(Num o) {
        int r;
        asm(
                "mov %1, %%eax;"
                "mov %%eax, %%ecx;"
                "mov %2, %%ebx;"
                "or %%ebx, %%ecx;"

                "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    int operator&(Num o) {
        int r;
        asm(
                "mov %1, %%eax;"
                "mov %%eax, %%ecx;"
                "mov %2, %%ebx;"
                "and %%ebx, %%ecx;"

                "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    int operator^(Num o) {
        int r;
        asm(
                "mov %1, %%eax;"
                "mov %%eax, %%ecx;"
                "mov %2, %%ebx;"
                "xor %%ebx, %%ecx;"

                "mov %%ecx, %0;"
                : "=m"(r)
                : "m"(val), "m"(o.val)
                );
        return r;
    }

    friend int operator~(Num o) {
        int r;
        asm(
                "mov %1, %%eax;"
                "mov %%eax, %%ebx;"
                "not %%ebx;"

                "mov %%ebx, %0;"
                : "=m"(r)
                : "m"(o.val)
                );
        return r;
    }

    int toInt() const {
        return val;
    }

    friend ostream &operator<<(ostream &os, const Num &n) {
        os << n.val;
        return os;
    }
};

int get(const int *arr, int i) {
    int r = 0;
    asm("mov %1, %%rax;"
        "mov %2, %%ebx;"
        "mov (%%rax, %%rbx, 4), %%ecx;"
        "add %%ecx, %0;"
        : "=m"(r)
        : "m"(arr), "m"(i)
        );
    return r;
}

void func() {
    cout << "Ya hochu pitsu!" << endl;
};

void Iter(void (*fptr)(), int n) {
    for (int i = 0; i < n; ++i) {
        asm("mov %0, %%rax;"
            "call *%%rax;"
            :
            : "m"(fptr));
    }
}

int main() {
    Num a(5);
    Num b(1);
    Num c = a + b;
    cout << a << " + " << b << " = " << c << endl;
    c = a - b;
    cout << a << " - " << b << " = " << c << endl;
    c = a * b;
    cout << a << " * " << b << " = " << c << endl;
    c = a / b;
    cout << a << " / " << b << " = " << c << endl;

    string r = ((a < b) ? "true" : "false");
    cout << a << " < " << b << " = " << r << endl;
    r = ((a > b) ? "true" : "false");
    cout << a << " > " << b << " = " << r << endl;
    r = ((a == b) ? "true" : "false");
    cout << a << " == " << b << " = " << r << endl;
    int v = (a | b);
    cout << a << " | " << b << " = " << v << endl;
    v = (a & b);
    cout << a << " & " << b << " = " << v << endl;
    v = (a ^ b);
    cout << a << " ^ " << b << " = " << v << endl;
    v = (~a);
    cout << "~" << a << " = " << v << endl;
    v = (a << b).toInt();
    cout << a << " << " << b << " = " << v << endl;
    v = (a >> b).toInt();
    cout << a << " >> " << b << " = " << v << endl;
    int arr[] = {1, 2, 3, 4, 5};
    int i = 0;
    v = get(arr, i);
    cout << "arr[" << i << "] = " << v << endl;
    int iter = 5;
    Iter(func, iter);

    return 0;
}
