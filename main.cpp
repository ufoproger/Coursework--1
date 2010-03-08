#include <algorithm>
#include <iostream>
#include <gtkmm.h>

#include "cpoints.h"

cPoints points;

Gtk::DrawingArea * pDA1;
Gtk::Statusbar * pSB1;
Gtk::Window * pWindow;
Gtk::ImageMenuItem * pIMI1; // Пункт меню "Открыть"
Gtk::ImageMenuItem * pIMI2; // Пункт меню "Сохранить"
Gtk::ImageMenuItem * pIMI6; // Пункт меню "Очистить"

bool pDA1_on_expose_event(GdkEventExpose*);
bool pDA1_on_button_press_event (GdkEventButton*);
bool pIMI1_on_button_press_event (GdkEventButton*);
bool pIMI2_on_button_press_event (GdkEventButton*);
bool pIMI6_on_button_press_event (GdkEventButton*);

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
	
	kit.run(*pWindow);

	return 0;
}

bool pDA1_on_expose_event(GdkEventExpose * event)
{
	Glib::RefPtr<Gdk::Window> window = pDA1->get_window();

	if (window)
	{
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		cr->rectangle(event->area.x, event->area.y, event->area.width, event->area.height);
		cr->clip();
		cr->set_line_width(10.0);
		cr->set_source_rgb(0.8, 0.0, 0.0);
		cr->fill();

		points.correct(event->area.width, event->area.height);

		for (int i = 1; i < points.size(); ++i)
		{
			cr->move_to(points[i - 1].x, points[i - 1].y);
			cr->line_to(points[i].x, points[i].y);
		}
		
		cr->stroke();
		cr->set_source_rgb(0.0, 0.0, 0.0);
		cr->set_line_width(12.0);
		
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
