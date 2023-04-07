/*
https://github.com/Josef-Friedrich/beep-melodies
*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

extern void playnote(char* note);

/*
play -q -n synth 0.5 pluck C4 vol 0.2
play -q -n synth 0.5 sine 1000 vol 0.2

*/
inline void playnote(char* note) {
    char cmd[50];
    if (' ' == note[0]) {
        sleep(0.5);
        return;
    }
    strcpy(cmd, "play -q -n synth 0.5 pluck ");
    strcat(cmd, note);
    strcat(cmd, " vol 0.1");
    system(cmd);
    // execlp("play", "play", "-q", "-n", "synth", "0.5", "pluck", "G4", NULL);

    return;
}

void test_playnote() {
    char song[] = "CDEFGAB";
    char note[3];
    note[1] = '4';
    note[2] = '\0';

    playnote("G");
    sleep(0.5);
    playnote("C");
    sleep(0.5);
    playnote("E");
    sleep(0.5);
    playnote("A");

    for (int i=0; i<strlen(song); i++) {
        note[0] = song[i];
        playnote(note);
        sleep(0.5);
    }
    return;
}

void test_playlittlestar() {
    char song[] = "CCGGAAG    FFEEDDC    GGFFEED    GGFFEED";
    char note[3];
    note[1] = '4';
    note[2] = '\0';

    for (int i=0; i<strlen(song); i++) {
        note[0] = song[i];
        playnote(note);
        sleep(0.5);
    }
    return;
}

/*
1234567
CDEFGAB
 67  1 2 7 1 1 1 7  12 7 1  1 1 2 3 2 3 2  3 3 2 3 5  3
爱你 孤身走暗 巷爱你 不跪的模 样爱你 对峙过绝 望不肯 哭一 场
*/
void test_playguyongzhe() {
    char song[] =    "ABCDBCCCBCDBCCCDEDEDEEDEGE";
    char yindiao[] = "44554555455455555555555555";
    char note[3];
    note[2] = '\0';

    for (int i=0; i<strlen(song); i++) {
        note[0] = song[i];
        note[1] = yindiao[i];
        playnote(note);
        sleep(0.1);
    }
    return;
}

void LED_ON(int leds[4]) {
    for (int i=0; i<4; i++)
        printf("%d ON\n", leds[i]);
    return;
}

void LED_OFF(int leds[4]) {
    for (int i=0; i<4; i++)
        printf("%d OFF\n", leds[i]);
    return;
}

int Note2Key(char *note) {
    // unsigned char pianokey[9][7] = {
    //   // C,  D,  E,  F,  G,  A,  B
    //     {00, 00, 00, 00, 00, 01, 03}, // 0
    //     {04, 06, 08, 09, 11, 13, 15}, // 1
    //     {16, 18, 20, 21, 23, 25, 27}, // 2
    //     {28, 30, 32, 33, 35, 37, 39}, // 3
    //     {40, 42, 44, 45, 47, 49, 51}, // 4
    //     {52, 54, 56, 57, 59, 61, 63}, // 5
    //     {64, 66, 68, 69, 71, 73, 75}, // 6
    //     {76, 78, 80, 81, 83, 85, 87}, // 7
    //     {88, 00, 00, 00, 00, 00, 00}, // 8
    // };
    unsigned char pianokey[9][12] = {
    // A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L
      {01, 03, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02}, // 0
      {13, 15, 04, 06, 08, 09, 11, 05, 07, 10, 12, 14}, // 1
      {25, 27, 16, 18, 20, 21, 23, 17, 19, 22, 24, 26}, // 2
      {37, 39, 28, 30, 32, 33, 35, 29, 31, 34, 36, 38}, // 3
      {49, 51, 40, 42, 44, 45, 47, 41, 43, 46, 48, 50}, // 4
      {61, 63, 52, 54, 56, 57, 59, 53, 55, 58, 60, 62}, // 5
      {73, 75, 64, 66, 68, 69, 71, 65, 67, 70, 72, 74}, // 6
      {85, 87, 76, 78, 80, 81, 83, 77, 79, 82, 84, 86}, // 7
      {00, 00, 88, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 8
    };

    return pianokey[(int)note[1], (int)(note[0]-'A')];
}

int getdengdaibynote(char *note) {
    if (('A'<=note[0]) && (note[0]<='G'))
        return 0;
}

int getledidbynote(char *note) {
    unsigned char ledids[9][12] = {
    // TODO: update the table values
    // A,  B,  C,  D,  E,  F,  G,  H,  I,  J,  K,  L
      {01, 03, 00, 00, 00, 00, 00, 00, 00, 00, 00, 02}, // 0
      {13, 15, 04, 06, 08, 09, 11, 00, 00, 00, 00, 00}, // 1
      {25, 27, 16, 18, 20, 21, 23, 00, 00, 00, 00, 00}, // 2
      {37, 39, 28, 30, 32, 33, 35, 00, 00, 00, 00, 00}, // 3
      {49, 51, 40, 42, 44, 45, 47, 00, 00, 00, 00, 00}, // 4
      {61, 63, 52, 54, 56, 57, 59, 00, 00, 00, 00, 00}, // 5
      {73, 75, 64, 66, 68, 69, 71, 00, 00, 00, 00, 00}, // 6
      {85, 87, 76, 78, 80, 81, 83, 00, 00, 00, 00, 00}, // 7
      {00, 00, 88, 00, 00, 00, 00, 00, 00, 00, 00, 00}, // 8
    };

    return ledids[(int)note[1], (int)(note[0]-'A')];

}

int main()
{
    // test_playnote();
    // test_playlittlestar();
    // test_playguyongzhe();
    char song1[][50] = {
        {"A   "}, // left key 1
        {"    "}, // left key 2
        {"  BB"}, // right key 1
        {"  CC"}, // right key 2
    };
    unsigned char notelen1[][50] = {
        {4, 0, 0, 0}, // left key duration
        {0, 0, 1, 1}, // right key duration
    };

    printf("%d\n", (int)strlen(song1[0]));
    // initializa curnotes
    char curnotes[11];
    int curleds[11];
    unsigned char curnotelen[2];
    int i=0;
    for (i=0; i<4; i++) {
        curnotes[i] = song1[i][0];
    }
    curnotes[i] = '\0';
    printf("%s\n", curnotes);
    for (i=0; i<2; i++) {
        curnotelen[i] = notelen1[i][0];
    }
    // LED ON for the first notes

    // loop xx cycles
    for (int i=0; i<strlen(song1[0]); i++) {
        // prepare LEDs to be ON
        for (int j=0; j<4; j++) {
            curnotes[j] += song1[j][i] - ' ';
            curleds[j] = getledbynote(curnotes[j]);
        }
        // LED ON
        LED_ON(curleds);
        sleep(0.5);

        // prepare LEDs to be OFF
        // update remaining time in curnotelen[]
        curnotelen[0] -= 1;
        curnotelen[1] -= 1;

        song1[][]
    }



    return 0;
}
