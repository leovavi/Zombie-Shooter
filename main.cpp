#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <sstream>

using namespace sf;
using namespace std;

int mover=0, mover2=0, mover3=0, mover4=0, estado=1, dificultad=7, vida1=4, vida2=4, vida3=4,vida4=4,sobrevivir=0,modo=10,dir=1;
int xzombie = 0, xzombie2 = 0, xzombie3 = 0, xzombie4 = 0;
bool vivo1=false, vivo2=false, modoo = false;
Texture backg, zombie, sol, sold, character2, zombie2, zombie3, zombie4, menu, gameover, bang, ganar;
Music gMusica;
SoundBuffer shot;
Font font;
Color color(230, 126, 34);
Text highscore;

void readHighscore(){
    ifstream in("highscore");
    int high = 0;
    in.read((char*)&high, 4);
    in.close();
    stringstream ss;
    ss << "Ultimo Puntaje: " << high;
    highscore.setString(ss.str());
    ss.str(string());
    highscore.setPosition(50, 450);
    highscore.setColor(color);
}

int main()
{
    RenderWindow app(VideoMode(1024, 512), "Zombie Shooter");

    backg.loadFromFile("fondo.jpg");
    gameover.loadFromFile("gameover.png");
    ganar.loadFromFile("ganar.png");
    menu.loadFromFile("fondomenu.png");
    character2.loadFromFile("rsz_sprite1flip.png");
    zombie.loadFromFile("zombie1.png");
    zombie3.loadFromFile("zombie1.png");
    zombie2.loadFromFile("zombie1flip.png");
    zombie4.loadFromFile("zombie1flip.png");
    sol.loadFromFile("nube.png");
    sold.loadFromFile("rsz_sprite1.png");
    bang.loadFromFile("rsz_boom.png");

    Sprite sbackg(backg);
    Sprite sgameover(gameover);
    Sprite sganar(ganar);
    Sprite smenu(menu);
    Sprite scharacter2(character2);
    Sprite szombie(zombie);
    Sprite szombie3(zombie3);
    Sprite szombie2(zombie2);
    Sprite szombie4(zombie4);
    Sprite ssol(sol);
    Sprite ssold(sold);
    Sprite sbang(bang);

    scharacter2.setPosition(370, 242);
    szombie.setPosition(-200, 220);
    szombie3.setPosition(-400, 220);
    szombie2.setPosition(900, 220);
    szombie4.setPosition(900, 220);
    ssol.setPosition(700, 10);
    ssold.setPosition(370, 242);
    sbang.setPosition(310, 292);

    gMusica.openFromFile("savage.wav");
    gMusica.play();
    gMusica.setLoop(true);

    shot.loadFromFile("gun.wav");
    Sound gShots(shot);

    font.loadFromFile("omb.ttf");
    highscore.setFont(font);
    readHighscore();

    while (app.isOpen())
    {
        Event event;
        app.clear();
        switch(estado){
        case 1:
            while(app.pollEvent(event)){
                if(event.type == Event::Closed)
                    app.close();

                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape)
                        app.close();

                    if(event.key.code == Keyboard::Num1)
                        dificultad = 12;
                    if(event.key.code == Keyboard::Num2)
                        dificultad = 7;
                    if(event.key.code == Keyboard::Num3)
                        dificultad = 4;
                    if(event.key.code == Keyboard::Num4)
                        modoo = true;
                    if(event.key.code == Keyboard::Return){
                        vivo1 = false; vivo2=false;
                        int y = szombie3.getPosition().y;
                        szombie3.setPosition(-110, y);
                        szombie.setPosition(-90, y);
                        szombie2.setPosition(900, y);
                        szombie4.setPosition(900, y);
                        vida1=4; vida2=4; vida3=4; vida4=4;
                        sobrevivir = 0;
                        modo = 10;
                        if(modoo)
                            modo = 10000;
                        estado = 2;
                    }
                }
            }
            app.draw(smenu);
            app.draw(highscore);
            break;

        case 2:
            if(vida1<=0 && vida2<=0 && vida3<=0 && vida4<=2){
                sobrevivir++;
                vivo1 = false; vivo2 = false;
                int y = szombie.getPosition().y;
                szombie3.setPosition(-250, y);
                szombie.setPosition(-250, y);
                szombie2.setPosition(900, y);
                szombie4.setPosition(900, y);
                vida1=4; vida2=4; vida3=4; vida4=4;
            }
            xzombie = szombie.getPosition().x;
            xzombie2 = szombie2.getPosition().x;
            xzombie3 = szombie3.getPosition().x;
            xzombie4 = szombie4.getPosition().x;

            if(xzombie>250 || xzombie2<500 || xzombie3>250 || xzombie4<500){
                ofstream out("highscore");
                out.write((char*)&sobrevivir, 4);
                out.close();
                modoo = false;
                estado = 3;
                break;
            }

            if(sobrevivir == modo){
                ofstream out("highscore");
                out.write((char*)&sobrevivir, 4);
                out.close();
                estado = 4;
                break;
            }

            if(vida1==0)
                vivo1 = true;
            if(vida2==0)
                vivo2 = true;

            if(mover%dificultad==0 && vida1>0)
                szombie.move(1, 0);
            if(vida1>=0)
                mover++;
            if(mover==10000)
                mover = 0;

            if(mover2%dificultad == 0 && vida2>0)
                szombie2.move(-1, 0);
            if(vida2>=0)
                mover2++;
            if(mover2==10000)
                mover2 = 0;

            if(mover3%dificultad==0 && vivo1 && vida3>0)
                szombie3.move(1, 0);
            if(vida3>=0)
                mover3++;
            if(mover3==10000)
                mover3 = 0;

            if(mover4%dificultad==0 && vivo2 && vida4>0)
                szombie4.move(-1, 0);
            if(vida4>=0)
                mover4++;
            if(mover4==10000)
                mover4 = 0;

            app.draw(sbackg);
            app.draw(ssol);
            if(dir==1){
                app.draw(ssold);
                sbang.setPosition(630, 292);
            }
            else if(dir!=1){
                app.draw(scharacter2);
                sbang.setPosition(310, 292);
            }
            if(vida1>0)
                app.draw(szombie);
            if(vida1<=2 && vida2>0)
                app.draw(szombie2);
            if(vida1<=2 && vida3>0)
                app.draw(szombie3);
            if(vida2<=2 && vida4>0)
                app.draw(szombie4);

            while(app.pollEvent(event)){
                if(event.type == Event::Closed)
                    app.close();

                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape)
                        app.close();

                    if(event.key.code == Keyboard::Space){
                        if(dir==2){
                            if(vida1>0)
                                vida1--;
                            else
                                vida3--;
                        }
                        else{
                            if(vida2>0)
                                vida2--;
                            else
                                vida4--;
                        }
                        gShots.play();
                        app.draw(sbang);
                    }

                    if(event.key.code == Keyboard::Left){
                        dir = 2;
                        sbang.setPosition(310, 292);
                    }
                    if(event.key.code == Keyboard::Right){
                        dir = 1;
                        sbang.setPosition(310, 292);
                    }
                }
            }
            break;

        case 3:
            app.draw(sgameover);
            while(app.pollEvent(event)){
                if(event.type == Event::Closed)
                    app.close();

                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape)
                        app.close();

                    if(event.key.code == Keyboard::Return){
                        readHighscore();
                        estado=1;
                    }
                }
            }
            break;

        case 4:
            app.draw(sganar);
            while(app.pollEvent(event)){
                if(event.type == Event::Closed)
                    app.close();

                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Escape)
                        app.close();

                    if(event.key.code == Keyboard::Return){
                        readHighscore();
                        estado=1;
                    }
                }
            }
        }
        app.display();
    }

    return EXIT_SUCCESS;
}
