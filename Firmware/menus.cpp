#include "menus.h"

#include <stdlib.h>  // calloc

static Adafruit_SSD1306* display_oled = NULL;

static inline uint16_t menu_color(uint8_t color) {
    return color ? SSD1306_WHITE : SSD1306_BLACK;
}

#define PIN_BTN_UP    32
#define PIN_BTN_DOWN  25
#define PIN_BTN_LEFT  33
#define PIN_BTN_RIGHT 35

static Button2 btn_up;
static Button2 btn_down;
static Button2 btn_left;
static Button2 btn_right;

// When false, button events are ignored (used by menu_manager_disable()).
static bool menu_buttons_enabled = false;

// Menu global
static menu_t menu = {0};

// Menu manager global
static menu_manager_t menu_manager = {0};

// flag for the first menu
static bool first_menu = true;

/**
 * @brief Callback function for the menu button press
 *
 * @param button The button that was pressed
 * @param event The event that occurred
 *
 * @return void
 */
void menu_button_callback(uint8_t button, uint8_t event) {

    // Only process the button press up
    if(event != BUTTON_PRESS_UP) {
        return;
    }

    if (button == BUTTON_LEFT) {
        if(menu_manager.current_index_menu > 0) {
            menu_manager.current_index_menu--;
            menu = menu_manager.menu_instances[menu_manager.current_index_menu];
            show_menu();
        }
        return;
    } 

    else if (button == BUTTON_RIGHT) {
        // Callback for the current menu
        menu.callback(menu.args, menu.index); 
        return;
    }

    else if (button == BUTTON_UP) {
        // If the index is 0, set it to the total menus
        if(menu.index == 0) {
            menu.index = menu.total_items;
        }
        menu.index--;

        show_menu();
    }

    // If the index is the total menus, set it to 0
    else if (button == BUTTON_DOWN) {
        menu.index++;

        if(menu.index == menu.total_items) {
            menu.index = 0;
        }

        show_menu();
    }
}

/**
 * @brief Button2 released handler. Forwards the release as a BUTTON_PRESS_UP
 *        event to the menu logic, using the button's ID as the identifier.
 *
 * @param btn The Button2 instance that fired
 *
 * @return void
 */
static void on_button_released(Button2& btn) {
    if (!menu_buttons_enabled) {
        return;
    }
    menu_button_callback((uint8_t)btn.getID(), BUTTON_PRESS_UP);
}

/**
 * @brief Configure the four Button2 instances once.
 *
 * @param void
 *
 * @return void
 */
static void menu_buttons_init(void) {
    static bool initialized = false;
    if (initialized) {
        return;
    }

    btn_up.begin(PIN_BTN_UP);
    btn_down.begin(PIN_BTN_DOWN);
    btn_left.begin(PIN_BTN_LEFT);
    btn_right.begin(PIN_BTN_RIGHT);

    btn_up.setID(BUTTON_UP);
    btn_down.setID(BUTTON_DOWN);
    btn_left.setID(BUTTON_LEFT);
    btn_right.setID(BUTTON_RIGHT);

    btn_up.setReleasedHandler(on_button_released);
    btn_down.setReleasedHandler(on_button_released);
    btn_left.setReleasedHandler(on_button_released);
    btn_right.setReleasedHandler(on_button_released);

    initialized = true;
}

/**
 * @brief Poll the Button2 instances. Call from loop().
 *
 * @param void
 *
 * @return void
 */
void menu_buttons_update(void) {
    btn_up.loop();
    btn_down.loop();
    btn_left.loop();
    btn_right.loop();
}

/**
 * @brief Draw the menu box
 *
 * @param pos The position of the menu box
 *
 * @return void
 */
static void draw_menu_box(uint8_t pos)
{
    
}

/**
 * @brief Draw the menu items to display_oled on the oled
 * 
 * @param void
 * 
 * @return void
 */
static void draw_menu_items(void){

    

}

/**
 * @brief Show the menu
 *
 * @param void
 *
 * @return void
 */
void show_menu(void) {

    if(display_oled == NULL) {
        return;
    }

    display_oled->clearDisplay();

    draw_menu_items();

    display_oled->display();
};

/**
 * @brief Clear the menu
 *
 * @param void
 *
 * @return void
 */
void clear_menu(void) {

    if(display_oled == NULL) {
        return;
    }
    
    display_oled->clearDisplay();
    display_oled->display();
}

/**
 * @brief Initialize the menu manager
 *
 * @param args The arguments for the menu
 * @param menu_instances The array of menu instances
 * @param total_menus The total number of menus
 *
 * @return void
 */
void menu_manager_init(Adafruit_SSD1306* display, void* args, menu_t* menu_instances, uint16_t total_menus) 
{

    if(display == NULL) {
        return;
    }

    display_oled = display;

    menu_manager.args = args;
    menu_manager.menu_instances = menu_instances;
    menu_manager.total_menus = total_menus;
    menu_manager.current_index_menu = 0;
    menu_manager.menu_order = (uint16_t*)calloc(total_menus, sizeof(uint16_t));

    // Text defaults for the menu rendering.
    display_oled->setTextColor(SSD1306_WHITE);
    display_oled->setTextSize(1);

    // Set up the buttons and start listening for events.
    menu_buttons_init();
    menu_buttons_enabled = true;
}

/**
 * @brief Go to the next menu
 *
 * @param id The id of the menu to go to
 *
 * @return void
 */
void menu__manager_next_menu(uint16_t id) 
{
    if(menu_manager.total_menus == 0) {
        return;
    }

    // Check if the id is valid
    if(id == menu_manager.total_menus) {
        return;
    }

    // Just used once 
    if(first_menu) {
        menu_manager.menu_order[0] = id;
        menu = menu_manager.menu_instances[id];
        first_menu = false;
        show_menu();
        return;
    }

    // If the current index is less than the total menus, increment the current index
    if(menu_manager.current_index_menu < menu_manager.total_menus) {

        // check if is not repeat it the menu
        if(menu_manager.menu_order[menu_manager.current_index_menu] != id) {
            menu_manager.current_index_menu++;
        }
    }

    menu_manager.menu_order[menu_manager.current_index_menu] = id;
    menu = menu_manager.menu_instances[id];
    show_menu();
}

/**
 * @brief Set the items for the menu
 *
 * @param items The items for the menu
 * @param total_items The total number of items
 * @param callback The callback for the menu
 * @param args The arguments for the menu
 *
 * @return void
 */
void menu_set_items(const char** items, uint32_t total_items, menu_callback_t callback, void* args) {
    menu.items = items;
    menu.total_items = total_items;
    menu.callback = callback;
    menu.args = args;
    menu.index = 0;
}

/**
 * @brief Set the selected item for the menu
 *
 * @param index The index of the selected item
 *
 * @return void
 */
void menu_set_selected_item(uint32_t index) {
    menu.index = index;
}


/**
 * @brief Reset the menu
 *
 * @param void
 *
 * @return void
 */
void menu_reset(void) {
    menu.args = NULL;
    menu.callback = NULL;
    menu.items = NULL;
    menu.total_items = 0;
    menu.index = 0;

    clearMenu();
}

/**
 * @brief Disable the menu manager
 *
 * @param void
 *
 * @return void
 */
void menuManagerDisable(void) {
    menu_buttons_enabled = false;
    clearMenu();
}

/**
 * @brief Go to the last menu when the user disable the menu manager
 *
 * @param void
 *
 * @return void
 */
void menuManagerEnable(void) {
    menu_buttons_enabled = true;
    showMenu();
}

/* 
--------------------------------------------------------------------------------
New version of menu manager
--------------------------------------------------------------------------------
*/

MenuManager_t::MenuManager_t(Adafruit_SSD1306* display, uint16_t total_items, const char** items, menu_callback_t callback, menu_callback_back_t callback_back, void* context)
{
    this->display_oled = display;
    this->total_items = total_items;
    this->items = items;
    this->callback = callback;
    this->callback_back = callback_back;
    this->context = context;
    this->current_item = 0;
}


// Private Functions

void MenuManager_t::showMenu(void)
{
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();
    this->drawMenu();
    this->display_oled->display();
}

void MenuManager_t::clearMenu(void)
{
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();
    this->display_oled->display();
}


void MenuManager_t::drawMenu(void){
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();

    this->drawMenuItems();

    this->display_oled->display();
}


void MenuManager_t::drawMenuBox(uint8_t pos){
    if(this->display_oled == NULL)
    {
        return;
    }

    int page = 3;
    int x = 0;

    if(pos > 2){
        pos = 2;
    }

    int y = 4 + (pos * 20);

    int width = 128 - 4;

    int height = (page * 8) - 6;

    this->display_oled->drawRect(x, y, width, height, menu_color(1));
    this->display_oled->drawRect(x, y, width - 1, height - 1, menu_color(1));

    // Top left border
    this->display_oled->drawPixel( x, y, menu_color(0));
    this->display_oled->drawPixel( x + 1, y, menu_color(0));
    this->display_oled->drawPixel( x, y + 1, menu_color(0));
    this->display_oled->drawPixel( x + 1, y + 1, menu_color(1));

    // Top right border
    this->display_oled->drawPixel( width - 1, y, menu_color(0));
    this->display_oled->drawPixel( width - 2, y, menu_color(0));
    this->display_oled->drawPixel( width - 1, y + 1, menu_color(0));
    this->display_oled->drawPixel( width - 2, y + 1, menu_color(1));

    // Bottom left border
    this->display_oled->drawPixel( x, y + height - 1, menu_color(0));
    this->display_oled->drawPixel( x + 1, y + height - 1, menu_color(0));
    this->display_oled->drawPixel( x, y + height - 2, menu_color(0));
    this->display_oled->drawPixel( x + 1, y + height - 2, menu_color(1));

    // Bottom right border
    this->display_oled->drawPixel( width - 1, y + height - 1, menu_color(0));
    this->display_oled->drawPixel( width - 2, y + height - 1, menu_color(0));
    this->display_oled->drawPixel( width - 1, y + height - 2, menu_color(0));
    this->display_oled->drawPixel( width - 2, y + height - 2, menu_color(1));
}


void MenuManager_t::drawMenuItems(void)
{
    if(this->display_oled == NULL)
    {
        return;
    }

    if(this->total_items == 0){
        return;
    }
    
    // Items to show on the menu (maximum 3)
    uint8_t items_to_show = (this->total_items < 3) ? this->total_items : 3;

    // Pivot for the item (start index of visible items)
    static uint32_t items_pivot = 0;
    static uint32_t last_total_items = 0;

    // Reset pivot when menu changes (total_items changes)
    if(last_total_items != this->total_items) {
        items_pivot = 0;
        last_total_items = this->total_items;
    }

    // Calculate pivot based on current index
    if(this->total_items <= 3) {
        // For 3 or fewer items, always start from 0
        items_pivot = 0;
    } else {
        // For more than 3 items, keep selected item in the middle when possible
        // Position 1 is the middle (0=top, 1=middle, 2=bottom)
        
        // Calculate desired pivot to keep selected item in middle
        uint32_t desired_pivot = (this->current_item > 0) ? this->current_item - 1 : 0;
        
        // Ensure we don't go beyond the end
        if(desired_pivot + 3 > this->total_items) {
            desired_pivot = this->total_items - 3;
        }
        
        items_pivot = desired_pivot;
    }

    // Validate pivot to prevent out-of-bounds access
    if(items_pivot + items_to_show > this->total_items) {
        items_pivot = (this->total_items >= items_to_show) ? this->total_items - items_to_show : 0;
    }

    // Position for the items
    for(uint8_t i = 0; i < items_to_show; i++){
        uint8_t y = 9 + (i * 20);
        uint32_t item_index = items_pivot + i;
        
        // Safety check to prevent out-of-bounds access
        if(item_index < this->total_items) {
            this->display_oled->setCursor(5, y);
            this->display_oled->print(this->items[item_index]);
        }
    }

    // Calculate selected item position on screen (0=top, 1=middle, 2=bottom)
    uint8_t selected_item = 0;
    if(this->current_item >= items_pivot && this->current_item < items_pivot + items_to_show) {
        selected_item = this->current_item - items_pivot;
    } else {
        // Fallback: if index is out of visible range, clamp it
        if(this->current_item < items_pivot) {
            selected_item = 0;
        } else {
            selected_item = items_to_show - 1;
        }
    }
    
    this->drawMenuBox(selected_item);
}


void MenuManager_t::onButtonReleased(Button2& btn)
{
    
    this->menuButtonCallback((uint8_t)btn.getID(), BUTTON_PRESS_UP);
    
}

void MenuManager_t::menuButtonCallback(uint8_t button, uint8_t event){
    // Missing this part
}