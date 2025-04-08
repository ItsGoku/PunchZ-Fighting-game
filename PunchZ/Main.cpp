/*
 * PunchZ - A 2D Fighting Game
 * Created by: Ali Yetkin Irmak
 * Date: 14.02.2025
 * Version: 1.0
 */


#include<windows.h>
#include"icb_gui.h"

int FRM; //frame
HANDLE hTimerQueue = NULL;
HANDLE hTimer = NULL;

int keypressed, keyreleased, lastpressed;

ICBYTES image, startingsc, chselect, winsc, chselectsc, bckgrnd, p1sprites, p1sprites2, startgame, p2sprites, p2sprites2, p1wins, p2wins;
ICBYTES p1frame, p2frame, p1bckg, p2bckg, p1standing, p2standing, p1forw, p2forw, p1backw, p2backw, p1atc1, p1atc2, p1atc3, p1atc4, p1atc5, p1airatc, p2atc1, p2atc2, p2atc3, p2atc4, p2atc5, p2airatc, p1jump, p2jump, p1blck, p2blck, p1dmg1, p1dmg2, p1dmg3, p2dmg1, p2dmg2, p2dmg3, p1defeat, p2defeat; //player sprites
ICBYTES p1standing2, p2standing2, p1forw2, p2forw2, p1backw2, p2backw2, p1atc12, p1atc22, p1atc32, p1atc42, p1atc52, p1airatc2, p2atc12, p2atc22, p2atc32, p2atc42, p2atc52, p2airatc2, p1jump2, p2jump2, p1blck2, p2blck2, p1dmg12, p1dmg22, p1dmg32, p2dmg12, p2dmg22, p2dmg32, p1defeat2, p2defeat2; //player sprites flipped


int sprites[2][2] = { {1,2} ,{3,4} }, row = 0, col = 0, player1, player2;

int p1x, p2x, p1y, p2y, p1comboc = 0, p2comboc = 0; //Players x and y cordinats
int p1health = 500, p2health = 0;

boolean p1inair = 0, p2inair = 0, p1moveleft, p1moveright, p2moveleft, p2moveright;
boolean pdir = 1; // starting direction is 1, reverse dircetion is 0
boolean p1atc, p2atc, p1gettinghit, p2gettinghit;//is player is attacking or taking damage
boolean p1block = 0, p2block = 0; //is player blocking

const DWORD COOLDOWN_TIME = 500; // Cooldown in milliseconds
DWORD p1LastAttackTime = 0, p2LastAttackTime = 0;      // Last attack timestamp



void ICGUI_Create()
{
    ICG_MWSize(1230, 850);
    ICG_MWTitle("PunchZ");
    ICG_MWColor(0, 0, 0);
}

void DrawP(bool p, int s) {     //funciton for drawing the player1 (1) or player2 (0) sprite
    if (p && pdir) {    //player1 in starting direction
        switch (s)
        {
        case 0:
            PasteNon0(p1standing, p1x, p1y, image);
            break;
        case 1:
            PasteNon0(p1forw, p1x, p1y, image);
            break;
        case 2:
            PasteNon0(p1backw, p1x, p1y, image);
            break;
        case 3:
            PasteNon0(p1atc1, p1x, p1y, image);
            break;
        case 4:
            PasteNon0(p1atc2, p1x, p1y, image);
            break;
        case 5:
            PasteNon0(p1atc3, p1x, p1y, image);
            break;
        case 6:
            PasteNon0(p1atc4, p1x, p1y, image);
            break;
        case 7:
            PasteNon0(p1atc5, p1x, p1y, image);
            break;
        case 8:
            PasteNon0(p1airatc, p1x, p1y, image);
            break;
        case 9:
            PasteNon0(p1jump, p1x, p1y, image);
            break;
        case 10:
            PasteNon0(p1dmg1, p1x, p1y, image);
            break;
        case 11:
            PasteNon0(p1dmg2, p1x, p1y, image);
            break;
        case 12:
            PasteNon0(p1dmg3, p1x, p1y, image);
            break;
        case 13:
            PasteNon0(p1blck, p1x, p1y, image);
            break;
        }
    }
    else if (!pdir && p) {  //player1 in opposite direction
        switch (s)
        {
        case 0:
            PasteNon0(p1standing2, p1x, p1y, image);
            break;
        case 2:
            PasteNon0(p1forw2, p1x, p1y, image);
            break;
        case 1:
            PasteNon0(p1backw2, p1x, p1y, image);
            break;
        case 3:
            PasteNon0(p1atc12, p1x, p1y, image);
            break;
        case 4:
            PasteNon0(p1atc22, p1x, p1y, image);
            break;
        case 5:
            PasteNon0(p1atc32, p1x, p1y, image);
            break;
        case 6:
            PasteNon0(p1atc42, p1x, p1y, image);
            break;
        case 7:
            PasteNon0(p1atc52, p1x, p1y, image);
            break;
        case 8:
            PasteNon0(p1airatc2, p1x, p1y, image);
            break;
        case 9:
            PasteNon0(p1jump2, p1x, p1y, image);
            break;
        case 10:
            PasteNon0(p1dmg12, p1x, p1y, image);
            break;
        case 11:
            PasteNon0(p1dmg22, p1x, p1y, image);
            break;
        case 12:
            PasteNon0(p1dmg32, p1x, p1y, image);
            break;
        case 13:
            PasteNon0(p1blck2, p1x, p1y, image);
            break;
        }
    }
    else if (!p && !pdir) { //player2 in opposite direction
        switch (s)
        {
        case 0:
            PasteNon0(p2standing, p2x, p2y, image);
            break;
        case 1:
            PasteNon0(p2forw, p2x, p2y, image);
            break;
        case 2:
            PasteNon0(p2backw, p2x, p2y, image);
            break;
        case 3:
            PasteNon0(p2atc1, p2x, p2y, image);
            break;
        case 4:
            PasteNon0(p2atc2, p2x, p2y, image);
            break;
        case 5:
            PasteNon0(p2atc3, p2x, p2y, image);
            break;
        case 6:
            PasteNon0(p2atc4, p2x, p2y, image);
            break;
        case 7:
            PasteNon0(p2atc5, p2x, p2y, image);
            break;
        case 8:
            PasteNon0(p2airatc, p2x, p2y, image);
            break;
        case 9:
            PasteNon0(p2jump, p2x, p2y, image);
            break;
        case 10:
            PasteNon0(p2dmg1, p2x, p2y, image);
            break;
        case 11:
            PasteNon0(p2dmg2, p2x, p2y, image);
            break;
        case 12:
            PasteNon0(p2dmg3, p2x, p2y, image);
            break;
        case 13:
            PasteNon0(p2blck, p2x, p2y, image);
            break;
        }
    }
    else {  //player2 in starting direction
        switch (s)
        {
        case 0:
            PasteNon0(p2standing2, p2x, p2y, image);
            break;
        case 1:
            PasteNon0(p2backw2, p2x, p2y, image);
            break;
        case 2:
            PasteNon0(p2forw2, p2x, p2y, image);
            break;
        case 3:
            PasteNon0(p2atc12, p2x, p2y, image);
            break;
        case 4:
            PasteNon0(p2atc22, p2x, p2y, image);
            break;
        case 5:
            PasteNon0(p2atc32, p2x, p2y, image);
            break;
        case 6:
            PasteNon0(p2atc42, p2x, p2y, image);
            break;
        case 7:
            PasteNon0(p2atc52, p2x, p2y, image);
            break;
        case 8:
            PasteNon0(p2airatc2, p2x, p2y, image);
            break;
        case 9:
            PasteNon0(p2jump2, p2x, p2y, image);
            break;
        case 10:
            PasteNon0(p2dmg12, p2x, p2y, image);
            break;
        case 11:
            PasteNon0(p2dmg22, p2x, p2y, image);
            break;
        case 12:
            PasteNon0(p2dmg32, p2x, p2y, image);
            break;
        case 13:
            PasteNon0(p2blck2, p2x, p2y, image);
            break;
        }
    }
    DisplayImage(FRM, image);
}

void FillBckg(boolean x) {      //fill the background of a player (true for p1,false for p2)

    if (x) {
        Copy(bckgrnd, p1x - 20, p1y - 20, 220, 220, p1bckg);
        PasteNon0(p1bckg, p1x - 20, p1y - 20, image);
    }
    else {
        Copy(bckgrnd, p2x - 20, p2y - 20, 220, 220, p2bckg);
        PasteNon0(p2bckg, p2x - 20, p2y - 20, image);
    }

}

void P_gotHit(boolean player) {     //function for the player to take damage

    int x;

    if (player) {
        p1gettinghit = 1;
        if (p1atc) return;
        if (pdir) x = -10;
        else x = 10;
        p1x += x;
        if (p1x < 40) p1x = 40;
        if (p1x > 1060) p1x = 1060;
        if (p1block) {
            FillBckg(0);
            DrawP(1, 13);
            if (p2inair) DrawP(0, 8);
            else if (p2comboc == 1) DrawP(0, 3);

            else if (p2comboc == 2) DrawP(0, 4);

            else if (p2comboc == 3) DrawP(0, 5);

            else if (p2comboc == 4) DrawP(0, 6);

            else if (p2comboc == 5) DrawP(0, 7);

            Sleep(500);
            p1gettinghit = 0;
            return;
        }
        p1health -= 20;
        FillRect(image, 70 + p1health, 30, 20, 60, 0xffffff);
        FillBckg(1);
        FillBckg(0);
        if (p2comboc == 1 || p2comboc == 2 || p2comboc == 3) DrawP(1, 10);
        else if (p2comboc == 4) DrawP(1, 11);
        else if (p2comboc == 5) DrawP(1, 12);

        if (p2inair) DrawP(0, 8);
        else if (p2comboc == 1) DrawP(0, 3);

        else if (p2comboc == 2) DrawP(0, 4);

        else if (p2comboc == 3) DrawP(0, 5);

        else if (p2comboc == 4) DrawP(0, 6);

        else if (p2comboc == 5) DrawP(0, 7);

        Sleep(500);
        p1gettinghit = 0;
    }
    else {
        p2gettinghit = 1;
        if (p2atc) return;
        if (pdir) x = 10;
        else x = -10;
        p2x += x;
        if (p2x < 40) p2x = 40;
        if (p2x > 1060) p2x = 1060;
        if (p2block) {
            FillBckg(1);
            DrawP(0, 13);
            if (p1inair) DrawP(1, 8);
            else if (p1comboc == 1) DrawP(1, 3);

            else if (p1comboc == 2) DrawP(1, 4);

            else if (p1comboc == 3) DrawP(1, 5);

            else if (p1comboc == 4) DrawP(1, 6);

            else if (p1comboc == 5) DrawP(1, 7);

            Sleep(500);
            p2gettinghit = 0;
            return;
        }

        p2health += 20;
        FillRect(image, 630, 30, p2health, 60, 0xffffff);
        FillBckg(0);
        FillBckg(1);

        if (p1comboc == 1 || p1comboc == 2 || p1comboc == 3) DrawP(0, 10);
        else if (p1comboc == 4) DrawP(0, 11);
        else if (p1comboc == 5) DrawP(0, 12);

        if (p1inair) DrawP(1, 8);
        else if (p1comboc == 1) DrawP(1, 3);

        else if (p1comboc == 2) DrawP(1, 4);

        else if (p1comboc == 3) DrawP(1, 5);

        else if (p1comboc == 4) DrawP(1, 6);

        else if (p1comboc == 5) DrawP(1, 7);

        Sleep(500);
        p2gettinghit = 0;
    }
}

void P_attack(boolean player) {     //function for player to attack

    static bool p1attacking;
    static bool p2attacking;

    int x;

    if (player == 1) {

        DWORD currentTime = GetTickCount();
        if ((currentTime - p1LastAttackTime) < COOLDOWN_TIME || p1attacking) {
            return;
        }

        p1LastAttackTime = currentTime;
        p1attacking = true;
        p1atc = p1attacking;
        p1comboc++;
        if (p1comboc == 6) p1comboc = 1;
        p1moveleft = 0;
        p1moveright = 0;

        if (pdir == 1) {
            x = 10;
            if (p1x + 180 > p2x) {
                p1x += x;
                if (p1x > 1060) p1x = 1060;
                P_gotHit(0);
            }
            else {
                FillBckg(1);
                if (p1inair) DrawP(1, 8);
                else if (p1comboc == 1) DrawP(1, 3);

                else if (p1comboc == 2) DrawP(1, 4);

                else if (p1comboc == 3) DrawP(1, 5);

                else if (p1comboc == 4) DrawP(1, 6);

                else if (p1comboc == 5) DrawP(1, 7);

                Sleep(500);
            }
        }
        else {
            x = -10;
            if (p1x - 60 < p2x + 120) {
                p1x += x;
                if (p1x < 40) p1x = 40;
                P_gotHit(0);
            }
            else {
                FillBckg(1);
                if (p1inair) DrawP(1, 8);
                else if (p1comboc == 1) DrawP(1, 3);

                else if (p1comboc == 2) DrawP(1, 4);

                else if (p1comboc == 3) DrawP(1, 5);

                else if (p1comboc == 4) DrawP(1, 6);

                else if (p1comboc == 5) DrawP(1, 7);

                Sleep(500);
            }
        }

        p1attacking = false;
        p1atc = p1attacking;
    }
    else {
        DWORD currentTime = GetTickCount();
        if ((currentTime - p2LastAttackTime) < COOLDOWN_TIME || p2attacking) {
            return;
        }

        p2LastAttackTime = currentTime;
        p2attacking = true;
        p2atc = p2attacking;
        p2comboc++;
        if (p2comboc == 6) p2comboc = 1;
        p2moveleft = 0;
        p2moveright = 0;

        if (pdir == 0) {
            x = 10;
            if (p2x + 180 > p1x) {
                p2x += x;
                if (p2x > 1060) p2x = 1060;
                P_gotHit(1);
            }
            else {
                FillBckg(0);
                if (p2inair) DrawP(0, 8);
                else if (p2comboc == 1) DrawP(0, 3);

                else if (p2comboc == 2) DrawP(0, 4);

                else if (p2comboc == 3) DrawP(0, 5);

                else if (p2comboc == 4) DrawP(0, 6);

                else if (p2comboc == 5) DrawP(0, 7);

                Sleep(500);
            }

        }
        else {
            x = -10;
            if (p2x - 60 < p1x + 120) {
                p2x += x;
                if (p2x < 40) p2x = 40;
                P_gotHit(1);
            }
            else {
                FillBckg(0);
                if (p2inair) DrawP(0, 8);
                else if (p2comboc == 1) DrawP(0, 3);

                else if (p2comboc == 2) DrawP(0, 4);

                else if (p2comboc == 3) DrawP(0, 5);

                else if (p2comboc == 4) DrawP(0, 6);

                else if (p2comboc == 5) DrawP(0, 7);

                Sleep(500);
            }

        }

        p2attacking = false;
        p2atc = p2attacking;
    }

}

void P_jump(boolean x) {    //function for player to jump

    boolean maxh = 0;

    if (x == 1) {

        p1y -= 250;
        p1inair = 1;

        while (p1inair) {
            if (maxh == 0) {

                p1y -= 5;

                Sleep(20);
                if (p1y == 200) maxh = 1;

            }
            else {
                if (p1atc) continue;
                else {
                    p1y += 5;

                    Sleep(10);
                    if (p1y == 500) {
                        p1inair = 0;
                        break;
                    }
                }
            }
        }
    }
    else {
        p2y -= 250;
        p2inair = 1;

        while (p2inair) {
            if (maxh == 0) {

                p2y -= 5;

                Sleep(20);
                if (p2y == 200) {
                    maxh = 1;
                }

            }
            else {
                if (p2atc) continue;
                else {
                    p2y += 5;

                    Sleep(10);
                    if (p2y == 500) {
                        p2inair = 0;
                        break;
                    }
                }
            }
        }
    }

}

// Thread called by the timer
VOID CALLBACK Player2Move(PVOID lpParam, BOOLEAN TimerOrWaitFired) //thread for player2 to move
{

    if (p2atc) return;
    if (p2gettinghit) return;

    if (p2block) {

        p2moveleft = 0;
        p2moveright = 0;
        FillBckg(0);
        DrawP(0, 13);
        return;
    }

    FillBckg(0);

    if (p2inair) {

        DrawP(0, 9);
    }
    else {
        if (p2moveleft == 0 && p2moveright == 0) DrawP(0, 0);
    }

    if (p1inair == p2inair) {
        if ((p2x + 105 < p1x && p1x < p2x + 135) || (p2x < p1x + 135 && p2x > p1x + 105)) {

            if (pdir == 0) p2moveright = 0;
            if (pdir == 1) p2moveleft = 0;
        }
    }

    if (p2moveleft) {
        p2comboc = 0;
        p2x -= 10;
        FillBckg(0);
        if (!p2inair) DrawP(0, 2);
        else DrawP(0, 9);
    }
    if (p2moveright) {
        p2comboc = 0;
        p2x += 10;
        FillBckg(0);
        if (!p2inair) DrawP(0, 1);
        else DrawP(0, 9);

    }
    if (keypressed == 38) {
        keypressed = NULL;
        p2comboc = 0;
        if (p2inair == 0) {
            FillBckg(0);
            P_jump(0);
        }

    }
    if (keypressed == 75) {
        lastpressed = keypressed;
        keypressed = NULL;
        P_attack(0);
    }

    if (p2x < 40) p2x = 40;
    if (p2x > 1000) p2x = 1000;


    Sleep(20);

}
// Thread called by the timer
VOID CALLBACK Player1Move(PVOID lpParam, BOOLEAN TimerOrWaitFired) //thread for player1 to move
{
    if (p1x + 20 > p2x) pdir = 0;
    else pdir = 1;

    if (p1health <= 0) {
        FillBckg(0);
        FillBckg(1);
        DrawP(0, 0);
        if (pdir) PasteNon0(p1defeat, p1x - 120, p1y + 90, image);
        else PasteNon0(p1defeat2, p1x, p1y + 90, image);

        DeleteTimerQueueEx(hTimerQueue, NULL);
        PlaySound("victory.Wav", NULL, SND_ASYNC);
        Copy(image, 1, 1, 1200, 800, winsc);
        PasteNon0(p2wins, 0, 0, winsc);
        DisplayImage(FRM, winsc);

    }
    else if (p2health >= 500) {
        FillBckg(0);
        FillBckg(1);
        DrawP(1, 0);
        if (pdir) PasteNon0(p2defeat2, p2x, p2y + 90, image);
        else PasteNon0(p2defeat, p2x - 120, p2y + 90, image);

        DeleteTimerQueueEx(hTimerQueue, NULL);
        PlaySound("victory.Wav", NULL, SND_ASYNC);
        Copy(image, 1, 1, 1200, 800, winsc);
        PasteNon0(p1wins, 0, 0, winsc);
        DisplayImage(FRM, winsc);

    }

    if (p1atc) return;
    if (p1gettinghit) return;

    if (p1block) {

        p1moveleft = 0;
        p1moveright = 0;
        FillBckg(1);
        DrawP(1, 13);
        return;
    }

    FillBckg(1);

    if (p1inair) {

        DrawP(1, 9);

    }
    else {
        if (p1moveleft == 0 && p1moveright == 0) DrawP(1, 0);
    }

    if (p1inair == p2inair) {
        if ((p1x + 105 < p2x && p2x < p1x + 135) || (p1x<p2x + 135 && p1x>p2x + 105)) {

            if (pdir == 1) p1moveright = 0;
            if (pdir == 0) p1moveleft = 0;
        }
    }

    if (p1moveleft) {
        p1comboc = 0;
        p1x -= 10;
        FillBckg(1);
        if (!p1inair) DrawP(1, 2);
        else DrawP(1, 9);


    }
    if (p1moveright) {
        p1comboc = 0;
        p1x += 10;
        FillBckg(1);
        if (!p1inair) DrawP(1, 1);
        else DrawP(1, 9);

    }

    if (keypressed == 87) {
        keypressed = NULL;
        p1comboc = 0;
        if (p1inair == 0) {
            FillBckg(1);
            P_jump(1);
        }

    }

    if (keypressed == 71) {
        keypressed = NULL;
        P_attack(1);
    }


    if (p1x < 40) p1x = 40;
    if (p1x > 1000) p1x = 1000;



    Sleep(20);

}

void WhenKeyPressed(int k)
{
    keypressed = k;
    if (keypressed == 70) p1block = 1;
    if (keypressed == 76) p2block = 1;
    if (keypressed == 65) p1moveleft = 1;
    if (keypressed == 68) p1moveright = 1;
    if (keypressed == 37) p2moveleft = 1;
    if (keypressed == 39) p2moveright = 1;
}
void WhenKeyReleased(int k)
{
    keyreleased = k;
    if (keyreleased == 70) p1block = 0;
    if (keyreleased == 76) p2block = 0;
    if (keyreleased == 65) p1moveleft = 0;
    if (keyreleased == 68) p1moveright = 0;
    if (keyreleased == 37) p2moveleft = 0;
    if (keyreleased == 39) p2moveright = 0;
}

void Play()
{
    ReadImage("bckgrnd.bmp", bckgrnd);
    ReadImage("p1win.bmp", p1wins);
    ReadImage("p2win.bmp", p2wins);
    CreateImage(image, 1200, 800, ICB_UINT);
    CreateImage(winsc, 1200, 800, ICB_UINT);

    image = 0;

    PasteNon0(bckgrnd, 0, 0, image);
    p1x = 100;
    p1y = 500;
    p2x = 980;
    p2y = 500;

    Copy(p1sprites, 51, 58, 195, 195, p1standing);
    Copy(p1sprites, 248, 68, 195, 195, p1forw);
    Copy(p1sprites, 447, 64, 195, 195, p1backw);
    Copy(p1sprites, 45, 279, 195, 195, p1atc1);
    Copy(p1sprites, 245, 279, 195, 195, p1atc2);
    Copy(p1sprites, 444, 275, 195, 195, p1atc3);
    Copy(p1sprites, 644, 278, 195, 195, p1atc4);
    Copy(p1sprites, 850, 279, 195, 195, p1atc5);
    Copy(p1sprites, 1066, 280, 195, 195, p1airatc);
    Copy(p1sprites, 630, 67, 195, 195, p1jump);
    Copy(p1sprites, 236, 498, 195, 195, p1dmg1);
    Copy(p1sprites, 438, 494, 195, 195, p1dmg2);
    Copy(p1sprites, 645, 495, 195, 195, p1dmg3);
    Copy(p1sprites, 30, 497, 195, 195, p1blck);
    Copy(p1sprites, 871, 555, 225, 118, p1defeat);

    Copy(p1sprites2, 1054, 58, 195, 195, p1standing2);
    Copy(p1sprites2, 857, 68, 195, 195, p1forw2);
    Copy(p1sprites2, 658, 64, 195, 195, p1backw2);
    Copy(p1sprites2, 1060, 279, 195, 195, p1atc12);
    Copy(p1sprites2, 860, 279, 195, 195, p1atc22);
    Copy(p1sprites2, 661, 275, 195, 195, p1atc32);
    Copy(p1sprites2, 461, 278, 195, 195, p1atc42);
    Copy(p1sprites2, 255, 279, 195, 195, p1atc52);
    Copy(p1sprites2, 39, 280, 195, 195, p1airatc2);
    Copy(p1sprites2, 475, 67, 195, 195, p1jump2);
    Copy(p1sprites2, 869, 498, 195, 195, p1dmg12);
    Copy(p1sprites2, 667, 494, 195, 195, p1dmg22);
    Copy(p1sprites2, 460, 495, 195, 195, p1dmg32);
    Copy(p1sprites2, 1075, 497, 195, 195, p1blck2);
    Copy(p1sprites2, 204, 555, 225, 118, p1defeat2);

    //player 2 sprites

    Copy(p2sprites, 51, 58, 195, 195, p2standing);
    Copy(p2sprites, 248, 68, 195, 195, p2forw);
    Copy(p2sprites, 447, 64, 195, 195, p2backw);
    Copy(p2sprites, 45, 279, 195, 195, p2atc1);
    Copy(p2sprites, 245, 279, 195, 195, p2atc2);
    Copy(p2sprites, 444, 275, 195, 195, p2atc3);
    Copy(p2sprites, 644, 278, 195, 195, p2atc4);
    Copy(p2sprites, 850, 279, 195, 195, p2atc5);
    Copy(p2sprites, 1066, 280, 195, 195, p2airatc);
    Copy(p2sprites, 630, 67, 195, 195, p2jump);
    Copy(p2sprites, 236, 498, 195, 195, p2dmg1);
    Copy(p2sprites, 438, 494, 195, 195, p2dmg2);
    Copy(p2sprites, 645, 495, 195, 195, p2dmg3);
    Copy(p2sprites, 30, 497, 195, 195, p2blck);
    Copy(p2sprites, 871, 555, 225, 118, p2defeat);

    Copy(p2sprites2, 1054, 58, 195, 195, p2standing2);
    Copy(p2sprites2, 857, 68, 195, 195, p2forw2);
    Copy(p2sprites2, 658, 64, 195, 195, p2backw2);
    Copy(p2sprites2, 1060, 279, 195, 195, p2atc12);
    Copy(p2sprites2, 860, 279, 195, 195, p2atc22);
    Copy(p2sprites2, 661, 275, 195, 195, p2atc32);
    Copy(p2sprites2, 461, 278, 195, 195, p2atc42);
    Copy(p2sprites2, 255, 279, 195, 195, p2atc52);
    Copy(p2sprites2, 39, 280, 195, 195, p2airatc2);
    Copy(p2sprites2, 475, 67, 195, 195, p2jump2);
    Copy(p2sprites2, 869, 498, 195, 195, p2dmg12);
    Copy(p2sprites2, 667, 494, 195, 195, p2dmg22);
    Copy(p2sprites2, 460, 495, 195, 195, p2dmg32);
    Copy(p2sprites2, 1075, 497, 195, 195, p2blck2);
    Copy(p2sprites2, 204, 555, 225, 118, p2defeat2);

    FillRect(image, 70, 30, 500, 60, 0xFF5733);
    FillRect(image, 630, 30, 500, 60, 0xFF5733);
    PasteNon0(p1standing, p1x, p1y, image);
    PasteNon0(p2standing2, p2x, p2y, image);
    DisplayImage(FRM, image);
    PlaySound("battle.Wav", NULL, SND_ASYNC);
    hTimerQueue = CreateTimerQueue();
    if (NULL == hTimerQueue)
    {
        return;
    }
    //starts 1000 ms later calls thread every 30 ms

    CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)Player1Move, NULL, 1000, 30, 0);
    CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)Player2Move, NULL, 1000, 30, 0);

    SetFocus(ICG_GetMainWindow());
}

void loadChamp(int x, int y) { //funciton for loading the selected characters
    switch (x)
    {
    case 1:
        ReadImage("Goku_sprite.bmp", p1sprites);
        ReadImage("Goku_sprite2.bmp", p1sprites2);
        break;
    case 2:
        ReadImage("Vegeta_sprite.bmp", p1sprites);
        ReadImage("Vegeta_sprite2.bmp", p1sprites2);
        break;
    case 3:
        ReadImage("Buu_sprite.bmp", p1sprites);
        ReadImage("Buu_sprite2.bmp", p1sprites2);
        break;
    case 4:
        ReadImage("Cooler_sprite.bmp", p1sprites);
        ReadImage("Cooler_sprite2.bmp", p1sprites2);
        break;
    }
    switch (y)
    {
    case 1:
        ReadImage("Goku_sprite.bmp", p2sprites);
        ReadImage("Goku_sprite2.bmp", p2sprites2);
        break;
    case 2:
        ReadImage("Vegeta_sprite.bmp", p2sprites);
        ReadImage("Vegeta_sprite2.bmp", p2sprites2);
        break;
    case 3:
        ReadImage("Buu_sprite.bmp", p2sprites);
        ReadImage("Buu_sprite2.bmp", p2sprites2);
        break;
    case 4:
        ReadImage("Cooler_sprite.bmp", p2sprites);
        ReadImage("Cooler_sprite2.bmp", p2sprites2);
        break;
    }
    Play();
}

void SelectCh(void*) { //player selection thread
    ICBYTES selectsprite, menu, p1goku, p2goku, p1vegeta, p2vegeta, p1buu, p2buu, p1cooler, p2cooler, goku, vegeta, buu, cooler, p1ch, p2ch;
    CreateImage(chselect, 1200, 800, ICB_UINT);
    ReadImage("menu.bmp", menu);
    PasteNon0(menu, 0, 0, chselect);
    ReadImage("selectsprite.bmp", selectsprite);
    Copy(menu, 50, 300, 500, 500, p1ch);
    Copy(menu, 850, 300, 500, 500, p2ch);
    Copy(selectsprite, 350, 100, 201, 301, goku);
    Copy(selectsprite, 850, 100, 201, 301, vegeta);
    Copy(selectsprite, 100, 100, 201, 301, buu);
    Copy(selectsprite, 600, 100, 201, 301, cooler);
    Copy(selectsprite, 350, 404, 200, 300, p1goku);
    Copy(selectsprite, 850, 404, 200, 300, p1vegeta);
    Copy(selectsprite, 100, 404, 200, 300, p1buu);
    Copy(selectsprite, 600, 404, 200, 300, p1cooler);
    Copy(selectsprite, 350, 694, 193, 288, p2goku);
    Copy(selectsprite, 839, 699, 215, 290, p2vegeta);
    Copy(selectsprite, 77, 690, 209, 275, p2buu);
    Copy(selectsprite, 608, 695, 182, 247, p2cooler);
    ReadImage("p1select.bmp", p1frame);
    ReadImage("p2select.bmp", p2frame);
    PasteNon0(goku, 400, 100, chselect);
    PasteNon0(vegeta, 600, 100, chselect);
    PasteNon0(buu, 400, 400, chselect);
    PasteNon0(cooler, 600, 400, chselect);
    PlaySound("Menu.Wav", NULL, SND_ASYNC);
    DisplayImage(FRM, chselect);
    while (player1 == NULL) {

        PasteNon0(p1ch, 50, 300, chselect);
        PasteNon0(goku, 400, 100, chselect);
        PasteNon0(vegeta, 600, 100, chselect);
        PasteNon0(buu, 400, 400, chselect);
        PasteNon0(cooler, 600, 400, chselect);

        if (keypressed == 39 && col < 1) {
            keypressed = NULL;
            col++;
        }
        if (keypressed == 37 && col > 0) {
            keypressed = NULL;
            col--;
        }
        if (keypressed == 40 && row < 1) {
            keypressed = NULL;
            row++;
        }
        if (keypressed == 38 && row > 0) {
            keypressed = NULL;
            row--;
        }

        if (sprites[row][col] == 1) {
            PasteNon0(p1frame, 401, 101, chselect);
            PasteNon0(p1goku, 100, 400, chselect);
        }
        if (sprites[row][col] == 2) {
            PasteNon0(p1frame, 601, 101, chselect);
            PasteNon0(p1vegeta, 100, 400, chselect);
        }
        if (sprites[row][col] == 3) {
            PasteNon0(p1frame, 401, 401, chselect);
            PasteNon0(p1buu, 100, 400, chselect);
        }
        if (sprites[row][col] == 4) {
            PasteNon0(p1frame, 601, 401, chselect);
            PasteNon0(p1cooler, 100, 400, chselect);
        }

        DisplayImage(FRM, chselect);

        if (keypressed == 13) {
            keypressed = NULL;
            player1 = sprites[row][col];
            row = 0;
            col = 0;
        }

        Sleep(20);
    }
    while (player2 == NULL) {

        PasteNon0(p2ch, 850, 300, chselect);
        PasteNon0(goku, 400, 100, chselect);
        PasteNon0(vegeta, 600, 100, chselect);
        PasteNon0(buu, 400, 400, chselect);
        PasteNon0(cooler, 600, 400, chselect);

        if (keypressed == 39 && col < 1) {
            keypressed = NULL;
            col++;
        }
        if (keypressed == 37 && col > 0) {
            keypressed = NULL;
            col--;
        }
        if (keypressed == 40 && row < 1) {
            keypressed = NULL;
            row++;
        }
        if (keypressed == 38 && row > 0) {
            keypressed = NULL;
            row--;
        }

        if (sprites[row][col] == 1) {
            PasteNon0(p2frame, 401, 101, chselect);
            PasteNon0(p2goku, 900, 400, chselect);
        }
        if (sprites[row][col] == 2) {
            PasteNon0(p2frame, 601, 101, chselect);
            PasteNon0(p2vegeta, 900, 400, chselect);
        }
        if (sprites[row][col] == 3) {
            PasteNon0(p2frame, 401, 401, chselect);
            PasteNon0(p2buu, 900, 400, chselect);
        }
        if (sprites[row][col] == 4) {
            PasteNon0(p2frame, 601, 401, chselect);
            PasteNon0(p2cooler, 900, 400, chselect);
        }

        DisplayImage(FRM, chselect);

        if (keypressed == 13) {
            keypressed = NULL;
            player2 = sprites[row][col];
            row = 0;
            col = 0;
            break;
        }

        Sleep(20);
    }
    PlaySound("ready.Wav", NULL, SND_SYNC);
    loadChamp(player1, player2);

}

void gamestart(void*) { //thread for game starting 
    DWORD dw;
    CreateImage(startingsc, 1200, 800, ICB_UINT);
    ReadImage("startgame.bmp", startgame);
    PasteNon0(startgame, 0, 0, startingsc);
    PlaySound("Opening.Wav", NULL, SND_ASYNC);
    DisplayImage(FRM, startingsc);
    while (true) {
        if (keypressed == 13) {
            keypressed = NULL;

            break;
        }
    }

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SelectCh, NULL, 0, &dw);

}

void ICGUI_main()
{
    DWORD dw;
    FRM = ICG_FrameMedium(0, 0, 1230, 850);
    ICG_SetOnKeyPressed(WhenKeyPressed);
    ICG_SetOnKeyUp(WhenKeyReleased);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)gamestart, NULL, 0, &dw);

}