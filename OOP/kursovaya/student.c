

struct student {
    int number;
    char group[6];
    char FIO[30];
    char birthday[11];
    int gender;
    int missedHours;
    int justifiedHours;
};

WCHAR* studentToString(struct student student) {
    WCHAR* str = (WCHAR*)malloc(128*sizeof(WCHAR));

    wsprintf(str, L"%d %s %s %s %d %d %d", student.number, student.group, student.FIO, student.birthday, student.gender, student.missedHours, student.justifiedHours);
    return str;
}