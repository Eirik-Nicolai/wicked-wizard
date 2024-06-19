#include "menu.hpp"

// template <typename T>
// Menu<T>::Menu()
// {
//   curr_selected = 0;
// }

// template <typename T>
// void Menu<T>::ScrollDown()
// {
//   curr_selected += 1;
//   if(curr_selected>=list_items.size()) curr_selected = 0;
// }

// template <typename T>
// void Menu<T>::ScrollUp()
// {
//   curr_selected -= 1;
//   if(curr_selected<0) curr_selected = list_items.size()-1;
// }

// template <typename T>
// void Menu<T>::Select()
// {
//   list_items[curr_selected].action();
// }

// template <typename T>
// int Menu<T>::ListSize() {return list_items.size();}

// template <typename T>
// void Menu<T>::AddItem(T t) {list_items.emplace_back(t);}

Menu::Menu()
{
  sel_row = 0;
  sel_col = 0;
}

SimpleMenu::SimpleMenu(MenuItem<std::string>& a) : Menu()
{
  items.emplace_back(a);
}

SimpleMenu::SimpleMenu(MenuItem<std::string> &a, MenuItem<std::string> &b) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
}

SimpleMenu::SimpleMenu(MenuItem<std::string> &a, MenuItem<std::string> &b, MenuItem<std::string> &c) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
  items.emplace_back(c);
}

SimpleMenu::SimpleMenu(MenuItem<std::string> &a, MenuItem<std::string> &b, MenuItem<std::string> &c, MenuItem<std::string> &d) : Menu()
{
  items.emplace_back(a);
  items.emplace_back(b);
  items.emplace_back(c);
  items.emplace_back(d);
}

void SimpleMenu::select()
{
  items[sel_row].select_cmd();
}

int SimpleMenu::size()
{
  return items.size();
}

bool SimpleMenu::is_hovered(int i)
{
  return i==sel_row;
}

void SimpleMenu::scroll_up()
{
  sel_row -= 1;
  if(sel_row<0) sel_row = items.size()-1;
}

void SimpleMenu::scroll_down()
{
  sel_row += 1;
  if(sel_row>=items.size()) sel_row = 0;
}

MenuItem<std::string> &SimpleMenu::operator [](int i){return items[i];}

ScrollableMenu::ScrollableMenu(std::vector<MenuItem<entt::entity>> &_items, int range) : Menu()
{
  inner_sel_row = 0;
  items = _items;
  inner_begin = items.begin();
  inner_size = items.size() > range ? range : items.size();
}

void ScrollableMenu::select()
{
  items[sel_row].select_cmd();
}

int ScrollableMenu::size()
{
  return items.size();
}

bool ScrollableMenu::is_hovered(int i)
{
  return i==inner_sel_row;
}

std::vector<MenuItem<entt::entity>> ScrollableMenu::get_inner()
{
  std::vector<MenuItem<entt::entity>> out;
  out.insert(out.cbegin(), inner_begin, inner_begin+inner_size);
  return out;
}

void ScrollableMenu::scroll_up()
{
  sel_row--;
  if(sel_row == -1)
  {
    sel_row = items.size()-1;
    inner_sel_row = inner_size-1;
    inner_begin = items.end()-inner_size;
  }
  else
  {
    if(inner_sel_row == 0)
    {
      inner_begin--;
    }
    else
    {
      inner_sel_row--;
    }
  }
  items[sel_row].scroll_cmd();
}

void ScrollableMenu::scroll_down()
{
  sel_row++;
  if(sel_row == items.size())
  {
    sel_row = inner_sel_row = 0;
    inner_begin = items.begin();
  }
  else
  {
    if(inner_sel_row == inner_size-1)
    {
      inner_begin++;
    }
    else
    {
      inner_sel_row++;
    }
  }
  items[sel_row].scroll_cmd();
}

template
<typename Type>
using list = std::vector<MenuItem<Type>>;

template
<typename Type>
MultiDimMenu<Type>::MultiDimMenu(list &l1) : Menu()
{
  items.emplace_back(l1);
}

template
<typename Type>
MultiDimMenu<Type>::MultiDimMenu(list &l1, list &l2) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
}

template
<typename Type>
MultiDimMenu<Type>::MultiDimMenu(list &l1, list &l2, list &l3) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
  items.emplace_back(l3);
}

template
<typename Type>
MultiDimMenu<Type>::MultiDimMenu(list &l1, list &l2, list &l3, list &l4) : Menu()
{
  items.emplace_back(l1);
  items.emplace_back(l2);
  items.emplace_back(l3);
  items.emplace_back(l4);
}

template
<typename Type>
void MultiDimMenu<Type>::select()
{
  items[sel_col][sel_row].select_cmd();
}

template
<typename Type>
int MultiDimMenu<Type>::size()
{
  return items.size();
}

template
<typename Type>
// TODO figure this out
bool MultiDimMenu<Type>::is_hovered(int r)
{
  std::cout << "NOT IMPL" << std::endl;
  return sel_row==r;
}

template
<typename Type>
bool MultiDimMenu<Type>::is_hovered(int c, int r)
{
  return sel_row==r && sel_col == c;
}

template
<typename Type>
MenuItem<Type> MultiDimMenu<Type>::get_hovered()
{
  if(sel_col < items.size())
  {
    if(sel_row < items[sel_col].size())
    {
      return items[sel_col][sel_row];
    }
    else
    {
      std::cout << "MultiDimMenu<Type>::get_hovered() row out of bounds" << std::endl;
      return items[sel_col][sel_row];
    }
  }
  std::cout << "MultiDimMenu<Type>::get_hovered() col out of bounds" << std::endl;
  return items[sel_col][sel_row];
}

template
<typename Type>
list<Type> &MultiDimMenu<Type>::operator [](int i)
{
  return items[i];
}

template
<typename Type>
void MultiDimMenu<Type>::scroll_up()
{
  sel_row -= 1;
  if(sel_row<0) sel_row = items[sel_col].size()-1;
}

template
<typename Type>
void MultiDimMenu<Type>::scroll_down()
{
  sel_row += 1;
  if(sel_row>=items[sel_col].size()) sel_row = 0;
}

template
<typename Type>
void MultiDimMenu<Type>::scroll_left()
{
  sel_col -= 1;
  if(sel_col<0) sel_col = items.size()-1;
  if(sel_row >= items[sel_col].size()) sel_row = items[sel_col].size()-1;
}

template
<typename Type>
void MultiDimMenu<Type>::scroll_right()
{
  sel_col += 1;
  if(sel_col>=items.size()) sel_col = 0;
  if(sel_row >= items[sel_col].size()) sel_row = items[sel_col].size()-1;
}

using combatlist = list<bool>;
using targetlist = list<entt::entity>;
using equipmentlist = list<entt::entity>;


CombatMenu::CombatMenu(combatlist& l1)
  : MultiDimMenu<bool>(l1) {}
CombatMenu::CombatMenu(combatlist& l1, combatlist& l2)
  : MultiDimMenu<bool>(l1, l2) {}
CombatMenu::CombatMenu(combatlist& l1, combatlist& l2, combatlist& l3)
  : MultiDimMenu<bool>(l1, l2, l3) {}
CombatMenu::CombatMenu(combatlist& l1, combatlist& l2, combatlist& l3, combatlist& l4)
  : MultiDimMenu<bool>(l1, l2, l3, l4) {}


TargetMenu::TargetMenu(targetlist& l1)
  : MultiDimMenu<entt::entity>(l1) {}
TargetMenu::TargetMenu(targetlist& l1, targetlist& l2)
  : MultiDimMenu<entt::entity>(l1, l2) {}
TargetMenu::TargetMenu(targetlist& l1, targetlist& l2, targetlist& l3)
  : MultiDimMenu<entt::entity>(l1, l2, l3) {}
TargetMenu::TargetMenu(targetlist& l1, targetlist& l2, targetlist& l3, targetlist& l4)
  : MultiDimMenu<entt::entity>(l1, l2, l3, l4) {}


EquipmentMenu::EquipmentMenu(equipmentlist& l1, equipmentlist& l2, equipmentlist& l3)
  : MultiDimMenu<entt::entity>(l1, l2, l3) {}
