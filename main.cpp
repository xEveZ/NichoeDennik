#define _MAIN_

#include "includer.h"

using namespace std;

SDL_DisplayMode info;

bool key[4]; /*su-0 / giù-1 / left-2 / right-3*/
double b,k,altezza_start;
void display();
void initOp();

///init classe..............................................................
                                apreImageAnimation* an[2];
                                _man* m;
///.........................................................................

apreImageAnimation* an_dx;
apreImageAnimation* an_run_dx;
apreImageAnimation* an_sx;
apreImageAnimation* an_run_sx;
apreImageAnimation* an_up_dx;
apreImageAnimation* an_up_sx;
apreImageAnimation* an_waiting;
apreAudio* background_audio;
apreImage* backimg,* ground/**,* shoot*/;
apreTimer* timer;   

bool shooting = false;

int main(int argc,char** argv)
{
    SDL_Init(SDL_INIT_EVERYTHING);



    SDL_Window *win;
    SDL_GLContext con;
    SDL_Event e;

    SDL_GetCurrentDisplayMode(0,&info);
    bool fullscreen=true;
    if(argc==3)
    {
        info.w=atoi(argv[1]);
        info.h=atoi(argv[2]);
        fullscreen=false;
    }
    win = SDL_CreateWindow("nemm", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, info.w, info.h, ((fullscreen) ? (SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN) : (SDL_WINDOW_OPENGL)));
    con = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(1);
    apreInit();

    bool esci=false;
    initOp();

    while(!esci)
    {
        display();
        SDL_GL_SwapWindow(win);
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    esci=true;
                break;
                case SDL_KEYUP:
                    if(e.key.keysym.scancode==SDL_SCANCODE_SPACE)
                        shooting=false;
                    if(e.key.keysym.scancode==SDL_SCANCODE_UP)
                        key[0]=false;
                    if(e.key.keysym.scancode==SDL_SCANCODE_DOWN)
                        key[1]=false;
                    if(e.key.keysym.scancode==SDL_SCANCODE_LEFT)
                        key[2]=false;
                    if(e.key.keysym.scancode==SDL_SCANCODE_RIGHT)
                        key[3]=false;
                break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                        esci=true;
                    if(e.key.keysym.scancode==SDL_SCANCODE_SPACE)
                        shooting=true;
                    if(e.key.keysym.scancode==SDL_SCANCODE_UP)
                        key[0]=true;
                    if(e.key.keysym.scancode==SDL_SCANCODE_DOWN)
                        key[1]=true;
                    if(e.key.keysym.scancode==SDL_SCANCODE_LEFT)
                        key[2]=true;
                    if(e.key.keysym.scancode==SDL_SCANCODE_RIGHT)
                        key[3]=true;

                break;
                default:
                break;
            }
        }

    }

    SDL_GL_DeleteContext(con);
    SDL_DestroyWindow(win);
    SDL_Quit();
    apreQuit();
    delete background_audio;
    delete an_dx;
    delete an_sx;
    delete an_run_dx;
    delete an_run_sx;
    delete an_up_dx;
    delete an_up_sx;
    delete an_waiting;
    delete timer;
///distruttore...........................................................................
                                m-> ~_man();
///......................................................................................
    return 0;
}

void initOp()
{
    glClearColor(1,0,0,1);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER,0.0);
    aprePack *pack;
    pack = new aprePack("nemm.aprepack");
///roba classe..............................................................................................

            an[0]=new apreImageAnimation();
            an[1]=new apreImageAnimation();
            an[0]->addFrame(new apreImage(new apreTexture(pack->getPack("still-dx.png"), APRE_IMAGE_PNG)));
            an[1]->addFrame(new apreImage(new apreTexture(pack->getPack("still-sx.png"), APRE_IMAGE_PNG)));
            m=new _man(an,400,300,0,100);
///fine roba classe.........................................................................................

    timer=new apreTimer();
    an_waiting=new apreImageAnimation(3);   ///animazione per quando è fermo e muove la testa di cazzo

    an_dx=new apreImageAnimation();
    an_run_dx=new apreImageAnimation(6);
    an_sx=new apreImageAnimation();
    an_run_sx = new apreImageAnimation(6);
    an_up_dx=new apreImageAnimation();
    an_up_sx=new apreImageAnimation();



    an_waiting->addFrame(new apreImage(new apreTexture(pack->getPack("still-dx.png"), APRE_IMAGE_PNG)));
    an_waiting->addFrame(new apreImage(new apreTexture(pack->getPack("still-sx.png"), APRE_IMAGE_PNG)));

    an_dx->addFrame(new apreImage(new apreTexture(pack->getPack("still-dx.png"), APRE_IMAGE_PNG)));
    an_run_dx->addFrame(new apreImage(new apreTexture(pack->getPack("run-1-dx.png"), APRE_IMAGE_PNG)));
    an_run_dx->addFrame(new apreImage(new apreTexture(pack->getPack("run-2-dx.png"), APRE_IMAGE_PNG)));
    an_run_dx->addFrame(new apreImage(new apreTexture(pack->getPack("run-3-dx.png"), APRE_IMAGE_PNG)));

    an_sx->addFrame(new apreImage(new apreTexture(pack->getPack("still-sx.png"), APRE_IMAGE_PNG)));
    an_run_sx->addFrame(new apreImage(new apreTexture(pack->getPack("run-1-sx.png"), APRE_IMAGE_PNG)));
    an_run_sx->addFrame(new apreImage(new apreTexture(pack->getPack("run-2-sx.png"), APRE_IMAGE_PNG)));
    an_run_sx->addFrame(new apreImage(new apreTexture(pack->getPack("run-3-sx.png"), APRE_IMAGE_PNG)));

    an_up_dx->addFrame(new apreImage(new apreTexture(pack->getPack("run-2-dx.png"), APRE_IMAGE_PNG)));
    an_up_sx->addFrame(new apreImage(new apreTexture(pack->getPack("run-2-sx.png"), APRE_IMAGE_PNG)));

    altezza_start=538;
    b=altezza_start;
    k=0;

    an_waiting->setPosition(k,b);
    an_waiting->setHeight(100);
    an_dx->setPosition(k,b);
    an_dx->setHeight(100);
    an_run_dx->setPosition(k,b);
    an_run_dx->setHeight(100);
    an_sx->setPosition(k,b);
    an_sx->setHeight(100);
    an_run_sx->setPosition(k,b);
    an_run_sx->setHeight(100);
    an_up_dx->setPosition(k,b);
    an_up_dx->setHeight(100);
    an_up_sx->setPosition(k,b);
    an_up_sx->setHeight(100);

    backimg = new apreImage(new apreTexture(pack->getPack("Background.png"),APRE_IMAGE_PNG));
    backimg->setImageWidth(info.w);
    backimg->setImagePos(0,0);
    ground = new apreImage(new apreTexture(pack->getPack("Ground.png"),APRE_IMAGE_PNG));
    ground->setImageWidth(info.w);
    ground->setImagePos(0,0);
    ///shoot = new apreImage(new apreTexture(pack->getPack("MMShoting.png"),APRE_IMAGE_PNG));
    ///shoot->setImageHeight(100);
    ///shoot->setImagePos(k,b);
    //background_audio = new apreAudio(pack->getPack("Kalimba.mp3"));
    //background_audio->play();

    delete pack;

}
bool go_up = false;
bool  _left = false;
bool a_terra=true;
bool first=true;            ///serve per fare girare la testa al tizio
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    backimg->draw();
    ground->draw();
                    ///draw classe...............................................................
                                                m->draw();
                    ///..........................................................................

  /**  if(shooting)
        shoot->draw();
*/

    if(key[0] && b==altezza_start)
    {
        go_up=true;
        a_terra=false;
        first=true;             ///ogni volta che premo un tasto diventa true
    }


    if(go_up)
    {
        b-=5;
        //cout<<"still here: "<<b<<endl<<"go_up"<<go_up<<endl;
        if(b>450)
        {
            an_up_dx->setPosition(k,b);
            an_up_sx->setPosition(k,b);
            if(!_left)
                an_up_dx->draw();
            else
                an_up_sx->draw();

        }
        else go_up=false;
    }
    if(!go_up)
    {
        if(b<altezza_start)
            {
                an_up_dx->setPosition(k,b+=5);
                an_up_sx->setPosition(k,b+=5);
                if(!_left)
                an_up_dx->draw();
                else
                an_up_sx->draw();
            }
    }
    if(b>altezza_start)
        b=altezza_start;
    if(b==altezza_start)
        a_terra=true;

    if(key[1]);
    if(key[2] && a_terra)
        {
            an_waiting->setPosition(--k,b);
            an_dx->setPosition(--k,b);
            an_run_dx->setPosition(--k,b);
            an_run_sx->setPosition(--k,b);
            an_sx->setPosition(--k,b);
            an_up_dx->setPosition(--k,b);
            an_up_sx->setPosition(--k,b);
            an_run_sx->draw();
            _left=true;
            first=true;
        }
    if (key[3] && a_terra)
    {
        an_waiting->setPosition(++k,b);
        an_dx->setPosition(++k,b);
        an_run_dx->setPosition(++k,b);
        an_run_sx->setPosition(++k,b);
        an_sx->setPosition(++k,b);
        an_up_dx->setPosition(++k,b);
        an_up_sx->setPosition(++k,b);
        an_run_dx->draw();
        _left=false;
        first=true;
    }

    if(!key[0] && !key[1] &&  !key[2] && !key[3] && a_terra )
       {
            if(first)
            {
                timer->start();
                first=false;
            }
            if(timer->isPassedMilliSecPeriod(4000)) ///ogni 4 secondi che è fermo gira la fottuta testa
                an_waiting->draw();
            else
            {
                if(!_left)
                    an_dx->draw();
                if(_left)
                    an_sx->draw();
            }
        }
    glFlush();
}
