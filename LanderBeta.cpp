#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <graphics.h>
#include <iostream>
#include <chrono>
#include <iostream>
#include <sys/time.h>
#include<conio.h>
#include<stdlib.h>



using namespace std;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;

int main() {

    void *p;

    int h=75, v=425, width=50, height=50, rlimit = 600, llimit = 1, ulimit = 1, dlimit=500, area;
    float spdown = 0.0, spright = 0.0;
    char stfloat[5];

    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto sec_since_epoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    auto oldmillisec_sinc_epoch = millisec_since_epoch;

    cout << "seconds since epoch: " << sec_since_epoch << endl;
    cout << "milliseconds since epoch: " << millisec_since_epoch << endl;

    initwindow(rlimit,dlimit,"The Lander Module Game - By Douglas");
    line(llimit, dlimit-50, rlimit-1, dlimit-50);

    //Create the image at the start
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
    // readimagefile("lander.jpg", h,v, h+width, v+height);
   // getimage(h,v, h+width, v+height, p);

    area = imagesize(h-(width/2),v-(width/2), h+(width/2), v+(height/2));
    p = malloc(area);
    getimage(h-(width/2),v-(width/2), h+(width/2), v+(height/2),p);
   // outtextxy(h, v-60, "speed down: ");
   // outtextxy(h, v-40, "speed right: ");
    cout << "speed right: "<< spright << "   -   speed down: " << spdown << endl;

  while(1)
  {
    if (GetKeyState(VK_LEFT) < 0) {
      cout << "Thrust Left!" << endl;
    }
    if (GetKeyState(VK_RIGHT) < 0) {
      cout << "Thrust Right" << endl;
    }
    if (GetKeyState(VK_UP) < 0) {
      cout << "speed down" << spdown << endl;
      spdown = spdown -.0001;

    }
    if (GetKeyState(VK_DOWN) < 0) {
      cout << "Thrust Down" << endl;
    }
    else if (GetKeyState(VK_ESCAPE) < 0) {
      break;
    }


    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    if( millisec_since_epoch > oldmillisec_sinc_epoch + 100)
    {
        cout << "Move Module!" << endl;
        //putimage(h,v, p, XOR_PUT);
        putimage(h-(width/2),v-(width/2), p, XOR_PUT);
        h = h + static_cast<int>(spright);
        v = v + static_cast<int>(spdown);
        if ( v < 10 ) break;

        putimage(h-(width/2),v-(width/2), p, XOR_PUT);
        //outtextxy(h, v-60, "speed down: ");
        //outtextxy(h, v-40, "speed right: ");


        //outtextxy(h+50, v-60, to_string(spdown) );
        //outtextxy(h+50, v-40, to_string(spright) );

        oldmillisec_sinc_epoch = millisec_since_epoch;
    }
  }

    return EXIT_SUCCESS;
}
