#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <graphics.h>
#include <sys/time.h>
#include <conio.h>
#include <stdlib.h>



using namespace std;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

//float to *char
char* DbleToAddrChar(double sprt) {

   string x = to_string(sprt);
    x.resize(10);
   // Allocate memory
   char* ccx = new char[10];

   // Copy contents
   std::copy(x.begin(), x.end(), ccx);

   return ccx;

}

//control lander
void landerControls()
{
    //pointers to memory locations
     void *p[8];
    // Define the play player position and height and width, and playffield limits
    int h=75, v=40, width=50, height=50, rlimit = 600, llimit = 1, ulimit = 1, dlimit=450, area;

    double spdown = 0.0, spright = 0.0;
    char stfloat[5];
    char spbuffr[7];
    char spbuffd[7];


    //set forces with 4 variables. thrustR = thrust right etc
    double thrustR = 0.0, thrustD = 0.0, thrustL = 0.0, thrustU = 0.0, gravity =0.1;
    int thrustcombo = 0;
    const string lander_fileNames[8] = {"lander.jpg", "lander1.jpg", "lander2.jpg", "lander3.jpg", "lander4.jpg", "lander5.jpg", "lander6.jpg", "lander7.jpg"};
    string spR,spD;

    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto sec_since_epoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    auto oldmillisec_sinc_epoch = millisec_since_epoch;

    cout << "seconds since epoch: " << sec_since_epoch << endl;
    cout << "milliseconds since epoch: " << millisec_since_epoch << endl;

    initwindow(rlimit,dlimit,"The Lander Module Game - By TruePath");

    //message board at bottom
    line(llimit, dlimit-50, rlimit-1, dlimit-50);
    line(rlimit-300, dlimit-50, rlimit-300, dlimit);
    line(llimit, dlimit-2, rlimit, dlimit-2);

    //display text on right- 2 lines of text on message board
    outtextxy( rlimit-295, dlimit-45, "MISSION DETAILS: You must land");
    outtextxy( rlimit-296, dlimit-25, "  without crashing.");

    //display speed righh and speed down on left
    outtextxy(llimit+5, dlimit-45, "Horizontal Speed: ");
    outtextxy(llimit+5, dlimit-25, "Vertical Speed:");

    /*
    setcolor(BLUE);
    circle(h, v, 25);
    setfillstyle(SOLID_FILL, BLUE);
    floodfill(h, v, BLUE);

    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(h-6, v-15, 2, 6);
    fillellipse(h+6, v-15, 2, 6);

    ellipse(h, v, 205, 335, 20, 9);
    ellipse(h, v, 205, 335, 20, 10);
    ellipse(h, v, 205, 335, 20, 11);
    */
    readimagefile("mountain.jpg", 200,200, rlimit-100,dlimit-50);

    for(int i = 0; i < 8; i++)
    {
        const char* constCharLanderFile = lander_fileNames[i].c_str();
        readimagefile( constCharLanderFile, h-(width/2), v-(height/2), h+(width/2), v+(height/2) );
        area = imagesize(h-(width/2),v-(height/2), h+(width/2), v+(height/2));
        p[i] = malloc(area);
        getimage(h-(width/2),v-(height/2), h+(width/2), v+(height/2),p[i]);

    }
/*

   // outtextxy(h, v-60, "speed down: ");
   // outtextxy(h, v-40, "speed right: ");

*/
    setfillstyle(HATCH_FILL,BLACK);
    rectangle(h-(width),v-(height/2), h+(width), v+(height/2));
    floodfill(h,v, BLACK);

    putimage(h-(width/2),v-(width/2), p[0], XOR_PUT);


  while(1)
  {

    if (GetKeyState(VK_RIGHT) < 0) {
         thrustR = 0.12345;
         } else {
        thrustR = 0.0;
        }

    if (GetKeyState(VK_LEFT) < 0)  {
        thrustL = 0.12345;

    } else {
         thrustL = 0.0;
    }

    if (GetKeyState(VK_UP) < 0)  {
        thrustU = 1.1234;

      } else  {
        thrustU = 0.0;
      }

/*    if (GetKeyState(VK_DOWN) < 0)  {
        thrustD = 0.1;
    } else {
        thrustD = 0.0;
    }
*/
    if (GetKeyState(VK_ESCAPE) < 0) {
        break;
    }



    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    if( millisec_since_epoch > oldmillisec_sinc_epoch + 100)
    {

        //calculate accelleration deceleration by forces applied
        spright += thrustR;
        spright -= thrustL;
        spdown -= thrustU;
        spdown += thrustD;
        spdown += gravity;

        //display speeds

       // string strDblSpRight = to_string(spright);
       // const char* constCharRight = strDblSpRight.c_str();
        outtextxy(llimit+150, dlimit-45, DbleToAddrChar(spright));
        outtextxy(llimit+125, dlimit-25, DbleToAddrChar(spdown));


        putimage(h-(width/2),v-(width/2), p[thrustcombo], XOR_PUT);
        h = h + static_cast<int>(spright);
        v = v + static_cast<int>(spdown);
        if ( h > rlimit || h < llimit || v < ulimit || v > dlimit) break;
        thrustcombo = 0;
        if (thrustR > 0.0) thrustcombo += 1;
        if (thrustL > 0.0) thrustcombo += 4;
        if (thrustU > 0.0) thrustcombo += 2;
        if (thrustcombo > 0) Beep(700,100);


        putimage(h-(width/2),v-(width/2), p[thrustcombo], XOR_PUT);

        oldmillisec_sinc_epoch = millisec_since_epoch;
    }
  }
    //return EXIT_SUCCESS;
    free(p);
}


int main() {

    landerControls();

    return EXIT_SUCCESS;
}
