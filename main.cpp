#include <algorithm>
#include <iostream>

#include "cpoint.h"

#include <glibmm.h>
#include <giomm.h>
#include <gdkmm.h>

#include <gtkmm/object.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/accelkey.h>
#include <gtkmm/accelgroup.h>
#include <gtkmm/adjustment.h>
#include <gtkmm/alignment.h>
#include <gtkmm/arrow.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/assistant.h>
#include <gtkmm/base.h>
#include <gtkmm/bin.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/cellview.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/checkmenuitem.h>
#include <gtkmm/cellrenderer.h>
#include <gtkmm/cellrendereraccel.h>
#include <gtkmm/cellrenderercombo.h>
#include <gtkmm/cellrendererpixbuf.h>
#include <gtkmm/cellrendererprogress.h>
#include <gtkmm/cellrendererspin.h>
#include <gtkmm/cellrenderertext.h>
#include <gtkmm/cellrenderertoggle.h>
#include <gtkmm/colorbutton.h>
#include <gtkmm/colorselection.h>
#include <gtkmm/combo.h>
#include <gtkmm/combobox.h>
#include <gtkmm/comboboxentry.h>
#include <gtkmm/comboboxentrytext.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/container.h>
#include <gtkmm/curve.h>
#include <gtkmm/dialog.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/editable.h>
#include <gtkmm/entry.h>
#include <gtkmm/expander.h>
#include <gtkmm/enums.h>
#include <gtkmm/eventbox.h>
#include <gtkmm/filechooser.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/filechooserwidget.h>
#include <gtkmm/filefilter.h>
#include <gtkmm/fileselection.h>
#include <gtkmm/fixed.h>
#include <gtkmm/fontbutton.h>
#include <gtkmm/fontselection.h>
#include <gtkmm/frame.h>
#include <gtkmm/handlebox.h>
#include <gtkmm/iconset.h>
#include <gtkmm/iconfactory.h>
#include <gtkmm/iconsource.h>
#include <gtkmm/icontheme.h>
#include <gtkmm/iconview.h>
#include <gtkmm/image.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/infobar.h>
#include <gtkmm/inputdialog.h>
#include <gtkmm/item.h>
#include <gtkmm/calendar.h>
#include <gtkmm/invisible.h>
#include <gtkmm/label.h>
#include <gtkmm/layout.h>
#include <gtkmm/liststore.h>
#include <gtkmm/listviewtext.h>
#include <gtkmm/linkbutton.h>
#include <gtkmm/main.h>
#include <gtkmm/menu.h>
#include <gtkmm/menu_elems.h>
#include <gtkmm/menubar.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/menushell.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/misc.h>
#include <gtkmm/notebook.h>
#include <gtkmm/object.h>
#include <gtkmm/optionmenu.h>
#include <gtkmm/paned.h>
#include <gtkmm/pagesetup.h>
#include <gtkmm/pagesetupunixdialog.h>
#include <gtkmm/papersize.h>
#include <gtkmm/printcontext.h>
#include <gtkmm/printer.h>
#include <gtkmm/printjob.h>
#include <gtkmm/printoperation.h>
#include <gtkmm/printoperationpreview.h>
#include <gtkmm/printsettings.h>
#include <gtkmm/printunixdialog.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/radioaction.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/radiomenuitem.h>
#include <gtkmm/radiotoolbutton.h>
#include <gtkmm/range.h>
#include <gtkmm/recentaction.h>
#include <gtkmm/recentchooser.h>
#include <gtkmm/recentchooserdialog.h>
#include <gtkmm/recentchoosermenu.h>
#include <gtkmm/recentchooserwidget.h>
#include <gtkmm/recentfilter.h>
#include <gtkmm/recentinfo.h>
#include <gtkmm/recentmanager.h>
#include <gtkmm/ruler.h>
#include <gtkmm/scale.h>
#include <gtkmm/scrollbar.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/separator.h>
#include <gtkmm/separatormenuitem.h>
#include <gtkmm/separatortoolitem.h>
#include <gtkmm/settings.h>
#include <gtkmm/sizegroup.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/statusicon.h>
#include <gtkmm/stock.h>
#include <gtkmm/stockid.h>
#include <gtkmm/stockitem.h>
#include <gtkmm/style.h>
#include <gtkmm/table.h>
#include <gtkmm/tearoffmenuitem.h>
#include <gtkmm/textbuffer.h>
#include <gtkmm/textchildanchor.h>
#include <gtkmm/textiter.h>
#include <gtkmm/textmark.h>
#include <gtkmm/texttag.h>
#include <gtkmm/texttagtable.h>
#include <gtkmm/textview.h>
#include <gtkmm/toggleaction.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolitem.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/toggletoolbutton.h>
#include <gtkmm/menutoolbutton.h>
#include <gtkmm/tooltip.h>
#include <gtkmm/tooltips.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treemodelfilter.h>
#include <gtkmm/treemodelsort.h>
#include <gtkmm/treepath.h>
#include <gtkmm/treerowreference.h>
#include <gtkmm/treeselection.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treeviewcolumn.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/viewport.h>
#include <gtkmm/widget.h>
#include <gtkmm/window.h>

#include "cpoints.h"

cPoints points;

Gtk::DrawingArea * pDA1;
Gtk::Statusbar * pSB1;
Gtk::Window * pWindow;
Gtk::ImageMenuItem * pIMI1; // Пункт меню "Открыть"
Gtk::ImageMenuItem * pIMI2; // Пункт меню "Сохранить"
Gtk::ImageMenuItem * pIMI6; // Пункт меню "Очистить"
Gtk::RadioMenuItem * pRMI1; // Радиопункт меню "Спираль справа"
Gtk::RadioMenuItem * pRMI2; // Радиопункт меню "Спираль слева"
Gtk::RadioMenuItem * pRMI3; // Радиопункт меню "Пульс справа"
Gtk::RadioMenuItem * pRMI4; // Радиопункт меню "Пульс слева"

bool pIMI1_on_button_press_event (GdkEventButton*);
bool pIMI2_on_button_press_event (GdkEventButton*);
bool pIMI6_on_button_press_event (GdkEventButton*);
bool pRMI1_on_button_press_event (GdkEventButton*);
bool pRMI2_on_button_press_event (GdkEventButton*);
bool pRMI3_on_button_press_event (GdkEventButton*);
bool pRMI4_on_button_press_event (GdkEventButton*);
bool pDA1_on_button_press_event (GdkEventButton*);
bool pDA1_on_expose_event(GdkEventExpose*);

int main (int argc, char *argv[])
{
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

	refBuilder->add_from_file("main_window.glade");

	refBuilder->get_widget("window1", pWindow);
	pWindow->set_default_size(400, 400);

	refBuilder->get_widget("drawingarea1", pDA1);
	pDA1->set_events(Gdk::BUTTON_PRESS_MASK);
	pDA1->signal_expose_event().connect(sigc::ptr_fun(pDA1_on_expose_event));
	pDA1->signal_button_press_event().connect(sigc::ptr_fun(pDA1_on_button_press_event));

	refBuilder->get_widget("statusbar1", pSB1);

	refBuilder->get_widget("imagemenuitem1", pIMI1);
	pIMI1->signal_button_press_event().connect(sigc::ptr_fun(pIMI1_on_button_press_event));
	
	refBuilder->get_widget("imagemenuitem2", pIMI2);
	pIMI2->signal_button_press_event().connect(sigc::ptr_fun(pIMI2_on_button_press_event));
	
	refBuilder->get_widget("imagemenuitem6", pIMI6);
	pIMI6->signal_button_press_event().connect(sigc::ptr_fun(pIMI6_on_button_press_event));
	
	refBuilder->get_widget("radiomenuitem1", pRMI1);
	pRMI1->signal_button_press_event().connect(sigc::ptr_fun(pRMI1_on_button_press_event));	

	refBuilder->get_widget("radiomenuitem2", pRMI2);
	pRMI2->signal_button_press_event().connect(sigc::ptr_fun(pRMI2_on_button_press_event));	

	refBuilder->get_widget("radiomenuitem3", pRMI3);
	pRMI3->signal_button_press_event().connect(sigc::ptr_fun(pRMI3_on_button_press_event));	
	
	refBuilder->get_widget("radiomenuitem4", pRMI4);
	pRMI4->signal_button_press_event().connect(sigc::ptr_fun(pRMI4_on_button_press_event));	

	kit.run(*pWindow);

	return 0;
}

bool pRMI1_on_button_press_event (GdkEventButton * event)
{
	points.set_calc_rule(true, true);
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	pSB1->push(Glib::ustring::compose("Выбран алгоритм построения ломаной \"%1\"", pRMI1->get_label()));
	return true;
}

bool pRMI2_on_button_press_event (GdkEventButton * event)
{
	points.set_calc_rule(true, false);
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	pSB1->push(Glib::ustring::compose("Выбран алгоритм построения ломаной \"%1\"", pRMI2->get_label()));
	return true;
}

bool pRMI3_on_button_press_event (GdkEventButton * event)
{
	points.set_calc_rule(false, true);
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	pSB1->push(Glib::ustring::compose("Выбран алгоритм построения ломаной \"%1\"", pRMI3->get_label()));
	return true;
}

bool pRMI4_on_button_press_event (GdkEventButton * event)
{
	points.set_calc_rule(false, false);
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	pSB1->push(Glib::ustring::compose("Выбран алгоритм построения ломаной \"%1\"", pRMI4->get_label()));
	return true;
}

bool pDA1_on_expose_event(GdkEventExpose * event)
{
	Glib::RefPtr<Gdk::Window> window = pDA1->get_window();

	if (window)
	{
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();
		cr->set_line_width(7.0);

		points.correct(event->area.width, event->area.height);

		for (int i = 1, color = 0; i < points.size(); ++i, color = (color + 1) % 2)
		{
			cr->set_source_rgba(0.7 + 0.2 * (float)color, 0.0, 0.0, 0.8);
			cr->move_to(points[i - 1].x, points[i - 1].y);
			cr->line_to(points[i].x, points[i].y);
			cr->stroke();
		}
		
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->set_line_width(9.0);
		
		for (int i = 0; i < points.size(); ++i)
		{
			cr->begin_new_sub_path();
			cr->arc(points[i].x, points[i].y, 0.6, 0, 6.28);
		}
		
		cr->stroke();		
	}

	return window;
}

bool pDA1_on_button_press_event (GdkEventButton * event)
{
	if (event->button == 1 && event->type == GDK_BUTTON_PRESS)
	{
		points.push(event->x, event->y, pDA1->get_width(), pDA1->get_height());
		pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
		pSB1->push(Glib::ustring::compose("Точка с координатами (%1, %2) добавлена на плоскость", event->x, event->y));
	}
	
	return true;
}

bool pIMI6_on_button_press_event (GdkEventButton * event)
{
	points.clear();
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	pSB1->push("Плоскость очищена от точек ломаной");

	return true;
}

bool pIMI1_on_button_press_event (GdkEventButton * event)
{
	Gtk::FileChooserDialog dialogFC(*pWindow, "Выберите файл с координатами точек");

	dialogFC.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialogFC.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);
	
	Gtk::FileFilter filter;
	filter.set_name("Текстовый файл");
	filter.add_pattern("*.txt");
	dialogFC.add_filter(filter);

	if (dialogFC.run() == Gtk::RESPONSE_OK)
	{
		cPoints newPoints;
		int count = newPoints.read_from_file(dialogFC.get_filename());
		
		pSB1->push(Glib::ustring::compose("Из файла \"%1\" прочитано точек: %2", dialogFC.get_filename(), count));

		if (count)
		{
			if (points.size())
			{
				Gtk::MessageDialog dialogM(*pWindow, "Объединить старые и новые координаты точек?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
				
				switch(dialogM.run())
				{
					case(Gtk::RESPONSE_YES):
					{
						points.push(newPoints);
						break;
					}
					case(Gtk::RESPONSE_NO):
					{
						points = newPoints;
						break;
					}
				}
			}
			else
				points = newPoints;
			
			pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());			
		}
		else
		{
			Gtk::MessageDialog dialogM(*pWindow, "В файле нет точек", false, Gtk::MESSAGE_ERROR);
			dialogM.set_secondary_text("Проверьте правильность указания координат точек в файле.");
			dialogM.run();
		}
	}
	return true;
}

bool pIMI2_on_button_press_event (GdkEventButton * event)
{
	Gtk::FileChooserDialog dialogFC(*pWindow, "Выберите файл для сохранения координат точек", Gtk::FILE_CHOOSER_ACTION_SAVE);

	dialogFC.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialogFC.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	
	Gtk::FileFilter filter;
	filter.set_name("Текстовый файл");
	filter.add_pattern("*.txt");
	dialogFC.add_filter(filter);

	if (dialogFC.run() == Gtk::RESPONSE_OK)
		if (points.save_to_file(dialogFC.get_filename()))
			pSB1->push(Glib::ustring::compose("Координаты точек сохранены в файл \"%1\" успешно", dialogFC.get_filename()));
		else
			pSB1->push(Glib::ustring::compose("Не удалось сохранить координаты точек в файл \"%1\"", dialogFC.get_filename()));

	return true;
}
