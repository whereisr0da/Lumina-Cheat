//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_TABS_HH
#define FGUI_TABS_HH

// includes
#include <vector>
#include <memory>
#include <string>

// library includes
#include "widgets.hpp"
#include "../dependencies/aliases.hpp"
#include "../dependencies/definitions.hpp"

namespace FGUI
{

class CForm;
class CGroupBox;
class CWidgets;

class CTabs
{
  friend class FGUI::CForm;
  friend class FGUI::CGroupBox;
public:

  // @brief: sets a custom title for the tab
  // @params: std::string title = title of the tab
  void SetTitle(std::string title);

  // @brief: get the tab's default title
  std::string GetTitle();

  // @brief: insert a new widget inside the tab
  // @params: std::shared_ptr<FGUI::CWidgets> widget instance (pointer)
  void AddWidget(std::shared_ptr<FGUI::CWidgets> widget);

  // @brief: set the default font of the tab
  // @params: std::string family = font family name, unsigned int size = font size, int flags = font flags, bool bold = make the font bold
  void SetFont(std::string family, unsigned int size, int flags = 0x0, bool bold = false);

  // @brief: set the default font of the tab
  // @params: FGUI::WIDGET_FONT font = widget font struct
  void SetFont(FGUI::WIDGET_FONT font);

  // @brief: get the tab's default font
  FGUI::FONT GetFont();

private:
  std::string m_strTitle;
  std::shared_ptr<FGUI::CForm> m_pParentForm;
  std::vector<std::shared_ptr<FGUI::CWidgets>> m_prgpWidgets;
  FGUI::FONT m_ulFont;
};

} // namespace FGUI

#endif // FGUI_TABS_HH