
struct a {
    char name[20];
};

struct b {
    char name[20];
};

struct c {
    struct a ola[10];
    struct b adeus[10];
};


int main() {
    struct c arr[20];
    return 0;
}