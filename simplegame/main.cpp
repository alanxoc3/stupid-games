#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cassert>
#include "src/sprite.h"
#include "src/player.h"
#include "src/score.h"
#include "src/constants.h"
#include "src/coin.h"
#include "src/spriteList.h"
#include "src/enemy.h"

bool initTest() {
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return 0;
   }

   if(!al_init_image_addon()) {
      fprintf(stderr, "failed to initialize image io!\n");
      return 0;
   }

   if (!al_install_keyboard()) {
      fprintf(stderr, "failed to install keyboard!\n");
      return 0;
   }

   al_init_font_addon();
   al_init_ttf_addon();

   return 1;
}

int main() {
   // The window.
   ALLEGRO_DISPLAY * display  = NULL;
   ALLEGRO_TIMER * timer = NULL;

   // The images.
   ALLEGRO_BITMAP * IMG_PLAYER = NULL;
   ALLEGRO_BITMAP * IMG_COIN   = NULL;
   ALLEGRO_BITMAP * IMG_BADOT  = NULL;
   ALLEGRO_BITMAP * IMG_BKGD   = NULL;
   ALLEGRO_BITMAP * IMG_BUTTON = NULL;
   ALLEGRO_FONT   * FONT       = NULL;

   // For events (Keyboard, timer, etc...)
   ALLEGRO_EVENT_QUEUE * event_queue = NULL;


   // Return an error if something goes bad.
   if(!initTest())
      return -1;

   display = al_create_display(ROOM_WIDTH, ROOM_HEIGHT);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   // Try to load all the images, if there is an error,
   // then exit the program.
   IMG_PLAYER = al_load_bitmap(FNAME_PLAYER);
   IMG_COIN   = al_load_bitmap(FNAME_COIN);
   IMG_BADOT  = al_load_bitmap(FNAME_BADOT);
   IMG_BKGD   = al_load_bitmap(FNAME_BKGD);
   IMG_BUTTON = al_load_bitmap(FNAME_BUTTON);

   // Load the font.
   FONT       = al_load_font(FNAME_FONT, FONT_SIZE, 0);

   if (!IMG_PLAYER || !IMG_COIN || !IMG_BADOT || !IMG_BKGD || !FONT) {
      fprintf(stderr, "failed to load resource.\n");

      // Destroy all the images just in case.
      al_destroy_bitmap(IMG_PLAYER);
      al_destroy_bitmap(IMG_COIN);
      al_destroy_bitmap(IMG_BADOT);
      al_destroy_bitmap(IMG_BKGD);
      al_destroy_bitmap(IMG_BUTTON);

      al_destroy_timer(timer);
      al_destroy_event_queue(event_queue);
      // Destroy the display.
      al_destroy_display(display);
      return -1;
   }

   // If the event_queue failed, still Null pointer.
   timer = al_create_timer(1.0 / FPS);
   event_queue = al_create_event_queue();
   if (!event_queue || !timer) {
      fprintf(stderr, "failed to create event_queue.");

      // Destroy all the images just in case.
      al_destroy_bitmap(IMG_PLAYER);
      al_destroy_bitmap(IMG_COIN);
      al_destroy_bitmap(IMG_BADOT);
      al_destroy_bitmap(IMG_BKGD);
      al_destroy_bitmap(IMG_BUTTON);

      // And the display.
      al_destroy_display(display);
      return -1;
   }

   // Add some events to your allegro thing :)
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(timer));


   // THE GAME STARTS HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   al_start_timer(timer);

   bool gameLoop = false;
   bool restart = true;
   const int xBut = (ROOM_WIDTH  - al_get_bitmap_width (IMG_BUTTON)) / 2;
   const int yBut = (ROOM_HEIGHT - al_get_bitmap_height(IMG_BUTTON)) / 2;

   Score points(FONT);

   while (restart) {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
      
      if (ev.type == ALLEGRO_EVENT_TIMER) {
         al_clear_to_color(al_map_rgb(50,100,240));
         al_draw_bitmap(IMG_BKGD, 0, 0, 0);
         al_draw_bitmap(IMG_BUTTON, xBut, yBut, 0);
         points.showHighScore();
         points.draw();
         points.hideHighScore();
         al_flip_display();
      } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_ENTER:
            case ALLEGRO_KEY_SPACE:
            case ALLEGRO_KEY_PAD_ENTER:
               gameLoop = true;
               break;
            case ALLEGRO_KEY_ESCAPE:
               restart = false;
               break;
            default: break;
         }
      } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         restart = false;
      }
      
      if (!gameLoop)
         continue;
      SpriteList list;
      Player * craft = new Player(IMG_PLAYER, &points);
      Coin * money = new Coin(IMG_COIN);
      Coin * money2 = new Coin(IMG_COIN);

      points.reset();
      list.add(craft);
      list.add(money);
      list.add(money2);
      int tmpScore = points.getScore();

      while (gameLoop && restart) {
         al_wait_for_event(event_queue, &ev);

         // Obtain input, even not in the time.
         craft->input(ev);

         if (ev.type == ALLEGRO_EVENT_TIMER) {
            // SCORE LOGIC
            if (points.getScore() > tmpScore) {
               tmpScore = points.getScore();
               if (points.getScore() % ENEMY_POWERUP_GAP  == 0)
                  list.powerUp();

               if (points.getScore() % ENEMY_SPAWN_GAP == 0)
                  list.add(new Enemy(IMG_BADOT, list));
            }

            list.move();
            list.collision();
            if (!craft->isAlive())
               gameLoop = false;

            // DRAW
            al_clear_to_color(al_map_rgb(50,100,240));
            al_draw_bitmap(IMG_BKGD, 0, 0, 0);
            list.draw();
            points.draw();
   
            al_flip_display();
            
         } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            restart = false;
         }
      }

      points.save();
   }

   // Destroy all the images just in case.
   al_destroy_bitmap(IMG_PLAYER);
   al_destroy_bitmap(IMG_COIN);
   al_destroy_bitmap(IMG_BADOT);
   al_destroy_bitmap(IMG_BKGD);
   al_destroy_bitmap(IMG_BUTTON);
   al_destroy_font(FONT);
   al_shutdown_font_addon();

   // Destroy the display.
   al_destroy_display    (display);

   // Destroy the event_queue.
   al_destroy_event_queue(event_queue);

   return 0;
}
