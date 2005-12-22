// A bunch of %rename directives generated by BuildRenamers in config.py
// in order to remove the wx prefix from all global scope names.

#ifndef BUILDING_RENAMERS

%rename(BU_LEFT)                            wxBU_LEFT;
%rename(BU_TOP)                             wxBU_TOP;
%rename(BU_RIGHT)                           wxBU_RIGHT;
%rename(BU_BOTTOM)                          wxBU_BOTTOM;
%rename(BU_ALIGN_MASK)                      wxBU_ALIGN_MASK;
%rename(BU_EXACTFIT)                        wxBU_EXACTFIT;
%rename(BU_AUTODRAW)                        wxBU_AUTODRAW;
%rename(Button)                             wxButton;
%rename(BitmapButton)                       wxBitmapButton;
%rename(CHK_2STATE)                         wxCHK_2STATE;
%rename(CHK_3STATE)                         wxCHK_3STATE;
%rename(CHK_ALLOW_3RD_STATE_FOR_USER)       wxCHK_ALLOW_3RD_STATE_FOR_USER;
%rename(CHK_UNCHECKED)                      wxCHK_UNCHECKED;
%rename(CHK_CHECKED)                        wxCHK_CHECKED;
%rename(CHK_UNDETERMINED)                   wxCHK_UNDETERMINED;
%rename(CheckBox)                           wxCheckBox;
%rename(Choice)                             wxChoice;
%rename(ComboBox)                           wxComboBox;
%rename(GA_HORIZONTAL)                      wxGA_HORIZONTAL;
%rename(GA_VERTICAL)                        wxGA_VERTICAL;
%rename(GA_SMOOTH)                          wxGA_SMOOTH;
%rename(GA_PROGRESSBAR)                     wxGA_PROGRESSBAR;
%rename(Gauge)                              wxGauge;
%rename(StaticBox)                          wxStaticBox;
%rename(StaticLine)                         wxStaticLine;
%rename(StaticText)                         wxStaticText;
%rename(StaticBitmap)                       wxStaticBitmap;
%rename(ListBox)                            wxListBox;
%rename(CheckListBox)                       wxCheckListBox;
%rename(TE_NO_VSCROLL)                      wxTE_NO_VSCROLL;
%rename(TE_AUTO_SCROLL)                     wxTE_AUTO_SCROLL;
%rename(TE_READONLY)                        wxTE_READONLY;
%rename(TE_MULTILINE)                       wxTE_MULTILINE;
%rename(TE_PROCESS_TAB)                     wxTE_PROCESS_TAB;
%rename(TE_LEFT)                            wxTE_LEFT;
%rename(TE_CENTER)                          wxTE_CENTER;
%rename(TE_RIGHT)                           wxTE_RIGHT;
%rename(TE_CENTRE)                          wxTE_CENTRE;
%rename(TE_RICH)                            wxTE_RICH;
%rename(TE_PROCESS_ENTER)                   wxTE_PROCESS_ENTER;
%rename(TE_PASSWORD)                        wxTE_PASSWORD;
%rename(TE_AUTO_URL)                        wxTE_AUTO_URL;
%rename(TE_NOHIDESEL)                       wxTE_NOHIDESEL;
%rename(TE_DONTWRAP)                        wxTE_DONTWRAP;
%rename(TE_CHARWRAP)                        wxTE_CHARWRAP;
%rename(TE_WORDWRAP)                        wxTE_WORDWRAP;
%rename(TE_BESTWRAP)                        wxTE_BESTWRAP;
%rename(TE_LINEWRAP)                        wxTE_LINEWRAP;
%rename(TE_RICH2)                           wxTE_RICH2;
%rename(TE_CAPITALIZE)                      wxTE_CAPITALIZE;
%rename(TEXT_ALIGNMENT_DEFAULT)             wxTEXT_ALIGNMENT_DEFAULT;
%rename(TEXT_ALIGNMENT_LEFT)                wxTEXT_ALIGNMENT_LEFT;
%rename(TEXT_ALIGNMENT_CENTRE)              wxTEXT_ALIGNMENT_CENTRE;
%rename(TEXT_ALIGNMENT_CENTER)              wxTEXT_ALIGNMENT_CENTER;
%rename(TEXT_ALIGNMENT_RIGHT)               wxTEXT_ALIGNMENT_RIGHT;
%rename(TEXT_ALIGNMENT_JUSTIFIED)           wxTEXT_ALIGNMENT_JUSTIFIED;
%rename(TEXT_ATTR_TEXT_COLOUR)              wxTEXT_ATTR_TEXT_COLOUR;
%rename(TEXT_ATTR_BACKGROUND_COLOUR)        wxTEXT_ATTR_BACKGROUND_COLOUR;
%rename(TEXT_ATTR_FONT_FACE)                wxTEXT_ATTR_FONT_FACE;
%rename(TEXT_ATTR_FONT_SIZE)                wxTEXT_ATTR_FONT_SIZE;
%rename(TEXT_ATTR_FONT_WEIGHT)              wxTEXT_ATTR_FONT_WEIGHT;
%rename(TEXT_ATTR_FONT_ITALIC)              wxTEXT_ATTR_FONT_ITALIC;
%rename(TEXT_ATTR_FONT_UNDERLINE)           wxTEXT_ATTR_FONT_UNDERLINE;
%rename(TEXT_ATTR_FONT)                     wxTEXT_ATTR_FONT;
%rename(TEXT_ATTR_ALIGNMENT)                wxTEXT_ATTR_ALIGNMENT;
%rename(TEXT_ATTR_LEFT_INDENT)              wxTEXT_ATTR_LEFT_INDENT;
%rename(TEXT_ATTR_RIGHT_INDENT)             wxTEXT_ATTR_RIGHT_INDENT;
%rename(TEXT_ATTR_TABS)                     wxTEXT_ATTR_TABS;
%rename(TE_HT_UNKNOWN)                      wxTE_HT_UNKNOWN;
%rename(TE_HT_BEFORE)                       wxTE_HT_BEFORE;
%rename(TE_HT_ON_TEXT)                      wxTE_HT_ON_TEXT;
%rename(TE_HT_BELOW)                        wxTE_HT_BELOW;
%rename(TE_HT_BEYOND)                       wxTE_HT_BEYOND;
%rename(OutOfRangeTextCoord)                wxOutOfRangeTextCoord;
%rename(InvalidTextCoord)                   wxInvalidTextCoord;
%rename(TextAttr)                           wxTextAttr;
%rename(TextCtrl)                           wxTextCtrl;
%rename(TextUrlEvent)                       wxTextUrlEvent;
%rename(ScrollBar)                          wxScrollBar;
%rename(SP_HORIZONTAL)                      wxSP_HORIZONTAL;
%rename(SP_VERTICAL)                        wxSP_VERTICAL;
%rename(SP_ARROW_KEYS)                      wxSP_ARROW_KEYS;
%rename(SP_WRAP)                            wxSP_WRAP;
%rename(SpinButton)                         wxSpinButton;
%rename(SpinCtrl)                           wxSpinCtrl;
%rename(SpinEvent)                          wxSpinEvent;
%rename(RadioBox)                           wxRadioBox;
%rename(RadioButton)                        wxRadioButton;
%rename(SL_HORIZONTAL)                      wxSL_HORIZONTAL;
%rename(SL_VERTICAL)                        wxSL_VERTICAL;
%rename(SL_TICKS)                           wxSL_TICKS;
%rename(SL_AUTOTICKS)                       wxSL_AUTOTICKS;
%rename(SL_LABELS)                          wxSL_LABELS;
%rename(SL_LEFT)                            wxSL_LEFT;
%rename(SL_TOP)                             wxSL_TOP;
%rename(SL_RIGHT)                           wxSL_RIGHT;
%rename(SL_BOTTOM)                          wxSL_BOTTOM;
%rename(SL_BOTH)                            wxSL_BOTH;
%rename(SL_SELRANGE)                        wxSL_SELRANGE;
%rename(SL_INVERSE)                         wxSL_INVERSE;
%rename(Slider)                             wxSlider;
%rename(ToggleButton)                       wxToggleButton;
%rename(BookCtrlBase)                       wxBookCtrlBase;
%rename(BookCtrlBaseEvent)                  wxBookCtrlBaseEvent;
%rename(NB_FIXEDWIDTH)                      wxNB_FIXEDWIDTH;
%rename(NB_TOP)                             wxNB_TOP;
%rename(NB_LEFT)                            wxNB_LEFT;
%rename(NB_RIGHT)                           wxNB_RIGHT;
%rename(NB_BOTTOM)                          wxNB_BOTTOM;
%rename(NB_MULTILINE)                       wxNB_MULTILINE;
%rename(NB_NOPAGETHEME)                     wxNB_NOPAGETHEME;
%rename(NB_HITTEST_NOWHERE)                 wxNB_HITTEST_NOWHERE;
%rename(NB_HITTEST_ONICON)                  wxNB_HITTEST_ONICON;
%rename(NB_HITTEST_ONLABEL)                 wxNB_HITTEST_ONLABEL;
%rename(NB_HITTEST_ONITEM)                  wxNB_HITTEST_ONITEM;
%rename(Notebook)                           wxNotebook;
%rename(NotebookEvent)                      wxNotebookEvent;
%rename(LB_DEFAULT)                         wxLB_DEFAULT;
%rename(LB_TOP)                             wxLB_TOP;
%rename(LB_BOTTOM)                          wxLB_BOTTOM;
%rename(LB_LEFT)                            wxLB_LEFT;
%rename(LB_RIGHT)                           wxLB_RIGHT;
%rename(LB_ALIGN_MASK)                      wxLB_ALIGN_MASK;
%rename(Listbook)                           wxListbook;
%rename(ListbookEvent)                      wxListbookEvent;
%rename(CHB_DEFAULT)                        wxCHB_DEFAULT;
%rename(CHB_TOP)                            wxCHB_TOP;
%rename(CHB_BOTTOM)                         wxCHB_BOTTOM;
%rename(CHB_LEFT)                           wxCHB_LEFT;
%rename(CHB_RIGHT)                          wxCHB_RIGHT;
%rename(CHB_ALIGN_MASK)                     wxCHB_ALIGN_MASK;
%rename(Choicebook)                         wxChoicebook;
%rename(ChoicebookEvent)                    wxChoicebookEvent;
%rename(TOOL_STYLE_BUTTON)                  wxTOOL_STYLE_BUTTON;
%rename(TOOL_STYLE_SEPARATOR)               wxTOOL_STYLE_SEPARATOR;
%rename(TOOL_STYLE_CONTROL)                 wxTOOL_STYLE_CONTROL;
%rename(TB_HORIZONTAL)                      wxTB_HORIZONTAL;
%rename(TB_VERTICAL)                        wxTB_VERTICAL;
%rename(TB_3DBUTTONS)                       wxTB_3DBUTTONS;
%rename(TB_FLAT)                            wxTB_FLAT;
%rename(TB_DOCKABLE)                        wxTB_DOCKABLE;
%rename(TB_NOICONS)                         wxTB_NOICONS;
%rename(TB_TEXT)                            wxTB_TEXT;
%rename(TB_NODIVIDER)                       wxTB_NODIVIDER;
%rename(TB_NOALIGN)                         wxTB_NOALIGN;
%rename(TB_HORZ_LAYOUT)                     wxTB_HORZ_LAYOUT;
%rename(TB_HORZ_TEXT)                       wxTB_HORZ_TEXT;
%rename(ToolBarToolBase)                    wxToolBarToolBase;
%rename(ToolBarBase)                        wxToolBarBase;
%rename(ToolBar)                            wxToolBar;
%rename(LC_VRULES)                          wxLC_VRULES;
%rename(LC_HRULES)                          wxLC_HRULES;
%rename(LC_ICON)                            wxLC_ICON;
%rename(LC_SMALL_ICON)                      wxLC_SMALL_ICON;
%rename(LC_LIST)                            wxLC_LIST;
%rename(LC_REPORT)                          wxLC_REPORT;
%rename(LC_ALIGN_TOP)                       wxLC_ALIGN_TOP;
%rename(LC_ALIGN_LEFT)                      wxLC_ALIGN_LEFT;
%rename(LC_AUTOARRANGE)                     wxLC_AUTOARRANGE;
%rename(LC_VIRTUAL)                         wxLC_VIRTUAL;
%rename(LC_EDIT_LABELS)                     wxLC_EDIT_LABELS;
%rename(LC_NO_HEADER)                       wxLC_NO_HEADER;
%rename(LC_NO_SORT_HEADER)                  wxLC_NO_SORT_HEADER;
%rename(LC_SINGLE_SEL)                      wxLC_SINGLE_SEL;
%rename(LC_SORT_ASCENDING)                  wxLC_SORT_ASCENDING;
%rename(LC_SORT_DESCENDING)                 wxLC_SORT_DESCENDING;
%rename(LC_MASK_TYPE)                       wxLC_MASK_TYPE;
%rename(LC_MASK_ALIGN)                      wxLC_MASK_ALIGN;
%rename(LC_MASK_SORT)                       wxLC_MASK_SORT;
%rename(LIST_MASK_STATE)                    wxLIST_MASK_STATE;
%rename(LIST_MASK_TEXT)                     wxLIST_MASK_TEXT;
%rename(LIST_MASK_IMAGE)                    wxLIST_MASK_IMAGE;
%rename(LIST_MASK_DATA)                     wxLIST_MASK_DATA;
%rename(LIST_SET_ITEM)                      wxLIST_SET_ITEM;
%rename(LIST_MASK_WIDTH)                    wxLIST_MASK_WIDTH;
%rename(LIST_MASK_FORMAT)                   wxLIST_MASK_FORMAT;
%rename(LIST_STATE_DONTCARE)                wxLIST_STATE_DONTCARE;
%rename(LIST_STATE_DROPHILITED)             wxLIST_STATE_DROPHILITED;
%rename(LIST_STATE_FOCUSED)                 wxLIST_STATE_FOCUSED;
%rename(LIST_STATE_SELECTED)                wxLIST_STATE_SELECTED;
%rename(LIST_STATE_CUT)                     wxLIST_STATE_CUT;
%rename(LIST_STATE_DISABLED)                wxLIST_STATE_DISABLED;
%rename(LIST_STATE_FILTERED)                wxLIST_STATE_FILTERED;
%rename(LIST_STATE_INUSE)                   wxLIST_STATE_INUSE;
%rename(LIST_STATE_PICKED)                  wxLIST_STATE_PICKED;
%rename(LIST_STATE_SOURCE)                  wxLIST_STATE_SOURCE;
%rename(LIST_HITTEST_ABOVE)                 wxLIST_HITTEST_ABOVE;
%rename(LIST_HITTEST_BELOW)                 wxLIST_HITTEST_BELOW;
%rename(LIST_HITTEST_NOWHERE)               wxLIST_HITTEST_NOWHERE;
%rename(LIST_HITTEST_ONITEMICON)            wxLIST_HITTEST_ONITEMICON;
%rename(LIST_HITTEST_ONITEMLABEL)           wxLIST_HITTEST_ONITEMLABEL;
%rename(LIST_HITTEST_ONITEMRIGHT)           wxLIST_HITTEST_ONITEMRIGHT;
%rename(LIST_HITTEST_ONITEMSTATEICON)       wxLIST_HITTEST_ONITEMSTATEICON;
%rename(LIST_HITTEST_TOLEFT)                wxLIST_HITTEST_TOLEFT;
%rename(LIST_HITTEST_TORIGHT)               wxLIST_HITTEST_TORIGHT;
%rename(LIST_HITTEST_ONITEM)                wxLIST_HITTEST_ONITEM;
%rename(LIST_NEXT_ABOVE)                    wxLIST_NEXT_ABOVE;
%rename(LIST_NEXT_ALL)                      wxLIST_NEXT_ALL;
%rename(LIST_NEXT_BELOW)                    wxLIST_NEXT_BELOW;
%rename(LIST_NEXT_LEFT)                     wxLIST_NEXT_LEFT;
%rename(LIST_NEXT_RIGHT)                    wxLIST_NEXT_RIGHT;
%rename(LIST_ALIGN_DEFAULT)                 wxLIST_ALIGN_DEFAULT;
%rename(LIST_ALIGN_LEFT)                    wxLIST_ALIGN_LEFT;
%rename(LIST_ALIGN_TOP)                     wxLIST_ALIGN_TOP;
%rename(LIST_ALIGN_SNAP_TO_GRID)            wxLIST_ALIGN_SNAP_TO_GRID;
%rename(LIST_FORMAT_LEFT)                   wxLIST_FORMAT_LEFT;
%rename(LIST_FORMAT_RIGHT)                  wxLIST_FORMAT_RIGHT;
%rename(LIST_FORMAT_CENTRE)                 wxLIST_FORMAT_CENTRE;
%rename(LIST_FORMAT_CENTER)                 wxLIST_FORMAT_CENTER;
%rename(LIST_AUTOSIZE)                      wxLIST_AUTOSIZE;
%rename(LIST_AUTOSIZE_USEHEADER)            wxLIST_AUTOSIZE_USEHEADER;
%rename(LIST_RECT_BOUNDS)                   wxLIST_RECT_BOUNDS;
%rename(LIST_RECT_ICON)                     wxLIST_RECT_ICON;
%rename(LIST_RECT_LABEL)                    wxLIST_RECT_LABEL;
%rename(LIST_FIND_UP)                       wxLIST_FIND_UP;
%rename(LIST_FIND_DOWN)                     wxLIST_FIND_DOWN;
%rename(LIST_FIND_LEFT)                     wxLIST_FIND_LEFT;
%rename(LIST_FIND_RIGHT)                    wxLIST_FIND_RIGHT;
%rename(ListItemAttr)                       wxListItemAttr;
%rename(ListItem)                           wxListItem;
%rename(ListEvent)                          wxListEvent;
%rename(ListView)                           wxListView;
%rename(TR_NO_BUTTONS)                      wxTR_NO_BUTTONS;
%rename(TR_HAS_BUTTONS)                     wxTR_HAS_BUTTONS;
%rename(TR_NO_LINES)                        wxTR_NO_LINES;
%rename(TR_LINES_AT_ROOT)                   wxTR_LINES_AT_ROOT;
%rename(TR_SINGLE)                          wxTR_SINGLE;
%rename(TR_MULTIPLE)                        wxTR_MULTIPLE;
%rename(TR_EXTENDED)                        wxTR_EXTENDED;
%rename(TR_HAS_VARIABLE_ROW_HEIGHT)         wxTR_HAS_VARIABLE_ROW_HEIGHT;
%rename(TR_EDIT_LABELS)                     wxTR_EDIT_LABELS;
%rename(TR_HIDE_ROOT)                       wxTR_HIDE_ROOT;
%rename(TR_ROW_LINES)                       wxTR_ROW_LINES;
%rename(TR_FULL_ROW_HIGHLIGHT)              wxTR_FULL_ROW_HIGHLIGHT;
%rename(TR_DEFAULT_STYLE)                   wxTR_DEFAULT_STYLE;
%rename(TR_TWIST_BUTTONS)                   wxTR_TWIST_BUTTONS;
%rename(TR_MAC_BUTTONS)                     wxTR_MAC_BUTTONS;
%rename(TR_AQUA_BUTTONS)                    wxTR_AQUA_BUTTONS;
%rename(TreeItemIcon_Normal)                wxTreeItemIcon_Normal;
%rename(TreeItemIcon_Selected)              wxTreeItemIcon_Selected;
%rename(TreeItemIcon_Expanded)              wxTreeItemIcon_Expanded;
%rename(TreeItemIcon_SelectedExpanded)      wxTreeItemIcon_SelectedExpanded;
%rename(TreeItemIcon_Max)                   wxTreeItemIcon_Max;
%rename(TREE_HITTEST_ABOVE)                 wxTREE_HITTEST_ABOVE;
%rename(TREE_HITTEST_BELOW)                 wxTREE_HITTEST_BELOW;
%rename(TREE_HITTEST_NOWHERE)               wxTREE_HITTEST_NOWHERE;
%rename(TREE_HITTEST_ONITEMBUTTON)          wxTREE_HITTEST_ONITEMBUTTON;
%rename(TREE_HITTEST_ONITEMICON)            wxTREE_HITTEST_ONITEMICON;
%rename(TREE_HITTEST_ONITEMINDENT)          wxTREE_HITTEST_ONITEMINDENT;
%rename(TREE_HITTEST_ONITEMLABEL)           wxTREE_HITTEST_ONITEMLABEL;
%rename(TREE_HITTEST_ONITEMRIGHT)           wxTREE_HITTEST_ONITEMRIGHT;
%rename(TREE_HITTEST_ONITEMSTATEICON)       wxTREE_HITTEST_ONITEMSTATEICON;
%rename(TREE_HITTEST_TOLEFT)                wxTREE_HITTEST_TOLEFT;
%rename(TREE_HITTEST_TORIGHT)               wxTREE_HITTEST_TORIGHT;
%rename(TREE_HITTEST_ONITEMUPPERPART)       wxTREE_HITTEST_ONITEMUPPERPART;
%rename(TREE_HITTEST_ONITEMLOWERPART)       wxTREE_HITTEST_ONITEMLOWERPART;
%rename(TREE_HITTEST_ONITEM)                wxTREE_HITTEST_ONITEM;
%rename(TreeItemId)                         wxTreeItemId;
%rename(TreeEvent)                          wxTreeEvent;
%rename(DIRCTRL_DIR_ONLY)                   wxDIRCTRL_DIR_ONLY;
%rename(DIRCTRL_SELECT_FIRST)               wxDIRCTRL_SELECT_FIRST;
%rename(DIRCTRL_SHOW_FILTERS)               wxDIRCTRL_SHOW_FILTERS;
%rename(DIRCTRL_3D_INTERNAL)                wxDIRCTRL_3D_INTERNAL;
%rename(DIRCTRL_EDIT_LABELS)                wxDIRCTRL_EDIT_LABELS;
%rename(GenericDirCtrl)                     wxGenericDirCtrl;
%rename(DirFilterListCtrl)                  wxDirFilterListCtrl;
%rename(PyControl)                          wxPyControl;
%rename(FRAME_EX_CONTEXTHELP)               wxFRAME_EX_CONTEXTHELP;
%rename(DIALOG_EX_CONTEXTHELP)              wxDIALOG_EX_CONTEXTHELP;
%rename(HelpEvent)                          wxHelpEvent;
%rename(ContextHelp)                        wxContextHelp;
%rename(ContextHelpButton)                  wxContextHelpButton;
%rename(HelpProvider)                       wxHelpProvider;
%rename(SimpleHelpProvider)                 wxSimpleHelpProvider;
%rename(DP_DEFAULT)                         wxDP_DEFAULT;
%rename(DP_SPIN)                            wxDP_SPIN;
%rename(DP_DROPDOWN)                        wxDP_DROPDOWN;
%rename(DP_SHOWCENTURY)                     wxDP_SHOWCENTURY;
%rename(DP_ALLOWNONE)                       wxDP_ALLOWNONE;
%rename(DatePickerCtrl)                     wxDatePickerCtrl;

#endif
