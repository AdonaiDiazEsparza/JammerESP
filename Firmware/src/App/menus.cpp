#include "menus.h"

// Maps a logical color (1 = foreground, 0 = background) to the SSD1306 color.
static inline uint16_t menu_color(uint8_t c)
{
    return c ? SSD1306_WHITE : SSD1306_BLACK;
}

Menus_t::Menus_t(Adafruit_SSD1306* display, uint16_t total_items, const char** items, menu_callback_t callback, menu_callback_back_t callback_back, void* context)
{
    this->display_oled = display;
    this->total_items = total_items;
    this->items = items;
    this->callback = callback;
    this->callback_back = callback_back;
    this->context = context;
    this->current_item = 0;
    this->btn_up = nullptr;
    this->btn_down = nullptr;
    this->btn_left = nullptr;
    this->btn_right = nullptr;
}


Menus_t::Menus_t(Adafruit_SSD1306* display)
{
    this->display_oled = display;
    this->items = nullptr;
    this->total_items = 0;
    this->callback = nullptr;
    this->callback_back = nullptr;
    this->context = nullptr;
    this->current_item = 0;
    this->btn_up = nullptr;
    this->btn_down = nullptr;
    this->btn_left = nullptr;
    this->btn_right = nullptr;
}


void Menus_t::setItems(const char** items, uint16_t total_items, menu_callback_t callback, menu_callback_back_t callback_back, void* context)
{
    this->items = items;
    this->total_items = total_items;
    this->callback = callback;
    this->callback_back = callback_back;
    this->context = context;
    this->current_item = 0;
    this->showMenu();
}

void Menus_t::setContext(void* context)
{
    this->context = context;
}

void Menus_t::setButtons(Button2* btn_up, Button2* btn_down, Button2* btn_left, Button2* btn_right)
{
    this->btn_up = btn_up;
    this->btn_down = btn_down;
    this->btn_left = btn_left;
    this->btn_right = btn_right;

    auto handler = [this](Button2& btn) { this->onButtonReleased(btn); };
    this->btn_up->setReleasedHandler(handler);
    this->btn_down->setReleasedHandler(handler);
    this->btn_left->setReleasedHandler(handler);
    this->btn_right->setReleasedHandler(handler);
}

void Menus_t::setSelectedItem(uint8_t item)
{
    this->current_item = item;
    this->showMenu();
}

void Menus_t::reset(void)
{
    // First clear the menu
    this->clearMenu();

    this->current_item = 0;
    this->items = NULL;
    this->total_items = 0;
    this->callback = NULL;
    this->callback_back = NULL;
    this->context = NULL;
}

void Menus_t::run(void){
    if(this->btn_up == NULL || this->btn_down == NULL ||
       this->btn_left == NULL || this->btn_right == NULL) {
        return;
    }

    this->btn_up->loop();
    this->btn_down->loop();
    this->btn_left->loop();
    this->btn_right->loop();
}

// Private functions

void Menus_t::showMenu(void)
{
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();
    this->drawMenu();
    this->display_oled->display();
}

void Menus_t::clearMenu(void)
{
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();
    this->display_oled->display();
}


void Menus_t::drawMenu(void){
    if(this->display_oled == NULL)
    {
        return;
    }

    this->display_oled->clearDisplay();

    this->drawMenuItems();

    this->display_oled->display();
}


void Menus_t::drawMenuBox(uint8_t pos){
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


void Menus_t::drawMenuItems(void)
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

    // Text style for the items (sin esto el texto queda negro sobre negro)
    this->display_oled->setTextSize(1);
    this->display_oled->setTextColor(menu_color(1));

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


void Menus_t::onButtonReleased(Button2& btn)
{
    
    this->menuButtonCallback((uint8_t)btn.getID(), BUTTON_PRESS_UP);
    
}

void Menus_t::menuButtonCallback(uint8_t button, uint8_t event){
    
    if (button == BUTTON_LEFT) {
        if(this->callback_back != NULL) {
            this->callback_back(this->context);
        }
        return;
    } 

    else if (button == BUTTON_RIGHT) {
        // Callback for the current menu
        if(this->callback != NULL) {
            this->callback(this->context, this->current_item); 
        }
        return;
    }

    else if (button == BUTTON_UP) {
        // If the index is 0, set it to the total menus
        if(this->current_item == 0) {
            this->current_item = this->total_items;
        }
        this->current_item--;

        this->showMenu();
    }

    // If the index is the total menus, set it to 0
    else if (button == BUTTON_DOWN) {
        this->current_item++;

        if(this->current_item == this->total_items) {
            this->current_item = 0; 
        }

        this->showMenu();
    }

}