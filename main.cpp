#include <algorithm>
#include <iostream>
#include <sstream>

#include <gtkmm.h>

#include "cmodelcolumns.h"
#include "cmarkedpoint.h"
#include "defines.h"
#include "cpoints.h"
#include "cpoint.h"


cPoints points[2];
size_t currPoints;

cModelColumns columns;

Glib::RefPtr<Gtk::ListStore> refTreeModel;

Gtk::ImageMenuItem 	*pIMI1; // Пункт меню "Открыть"
Gtk::ImageMenuItem 	*pIMI2; // Пункт меню "Сохранить"
Gtk::ImageMenuItem 	*pIMI3; // Пункт меню "О программе"
Gtk::ImageMenuItem	*pIMI6; // Пункт меню "Очистить"
Gtk::AboutDialog	*pAD1;
Gtk::DrawingArea	*pDA1;
Gtk::Statusbar		*pSB1;
Gtk::MenuItem		*pMI3; // Пункт контекстного меню "Выделить всё"
Gtk::MenuItem		*pMI4; // Пункт контекстного меню "Снять выделение"
Gtk::MenuItem		*pMI5; // Пункт контекстного меню "Удалить выделенное"
Gtk::MenuItem		*pMI7;
Gtk::MenuItem		*pMI8;
Gtk::TreeView		*pTrV1;
Gtk::TextView		*pTeV1;
Gtk::Notebook		*pNB1;
Gtk::Window			*pWindow;
Gtk::Button			*pB1;
Gtk::Button			*pB2;
Gtk::Menu			*pM3;
Gtk::Menu			*pM5;

bool pIMI1_on_button_press_event (GdkEventButton*);
bool pIMI2_on_button_press_event (GdkEventButton*);
bool pIMI3_on_button_press_event (GdkEventButton*);
bool pIMI6_on_button_press_event (GdkEventButton*);
bool pMI3_on_button_press_event (GdkEventButton*);
bool pMI4_on_button_press_event (GdkEventButton*);
bool pMI5_on_button_press_event (GdkEventButton*);
bool pMI7_on_button_press_event (GdkEventButton*);
bool pMI8_on_button_press_event (GdkEventButton*);
bool pDA1_on_button_press_event (GdkEventButton*);
bool pTrV1_on_button_press_event(GdkEventButton*);
bool pDA1_on_expose_event (GdkEventExpose*);
void pAD1_on_about_dialog_response (int);
void pB1_on_button_press_event ();
void pB2_on_button_press_event ();
void pNB1_on_switch_page (GtkNotebookPage*, guint);
void pTrV1_update_list ();
void pTrV1_save_list ();

int main (int argc, char *argv[])
{
	currPoints = 0;

	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();

	refBuilder->add_from_file("main_window.glade");

	refBuilder->get_widget("window1", pWindow);
	pWindow->set_default_size(400, 400);
	pWindow->set_title(Glib::ustring("Курсовая работа"));
	
	refBuilder->get_widget("drawingarea1", pDA1);
	pDA1->set_events(Gdk::BUTTON_PRESS_MASK);
	pDA1->signal_expose_event().connect(sigc::ptr_fun(pDA1_on_expose_event));
	pDA1->signal_button_press_event().connect(sigc::ptr_fun(pDA1_on_button_press_event));

	refBuilder->get_widget("statusbar1", pSB1);

	refBuilder->get_widget("imagemenuitem1", pIMI1);
	pIMI1->signal_button_press_event().connect(sigc::ptr_fun(pIMI1_on_button_press_event));
	
	refBuilder->get_widget("imagemenuitem2", pIMI2);
	pIMI2->signal_button_press_event().connect(sigc::ptr_fun(pIMI2_on_button_press_event));
	
	refBuilder->get_widget("menuitem3", pMI3);
	pMI3->signal_button_press_event().connect(sigc::ptr_fun(pMI3_on_button_press_event));
	
	refBuilder->get_widget("menuitem4", pMI4);
	pMI4->signal_button_press_event().connect(sigc::ptr_fun(pMI4_on_button_press_event));
	
	refBuilder->get_widget("menuitem5", pMI5);
	pMI5->signal_button_press_event().connect(sigc::ptr_fun(pMI5_on_button_press_event));

	refBuilder->get_widget("imagemenuitem3", pIMI3);
	pIMI3->signal_button_press_event().connect(sigc::ptr_fun(pIMI3_on_button_press_event));
	
	refBuilder->get_widget("imagemenuitem6", pIMI6);
	pIMI6->signal_button_press_event().connect(sigc::ptr_fun(pIMI6_on_button_press_event));

	refBuilder->get_widget("aboutdialog1", pAD1);
	pAD1->signal_response().connect(sigc::ptr_fun(pAD1_on_about_dialog_response));

	refBuilder->get_widget("menu5", pM5);

	refBuilder->get_widget("menuitem7", pMI7);
	pMI7->signal_button_press_event().connect(sigc::ptr_fun(pMI7_on_button_press_event));

	refBuilder->get_widget("menuitem8", pMI8);
	pMI8->signal_button_press_event().connect(sigc::ptr_fun(pMI8_on_button_press_event));

	refBuilder->get_widget("button1", pB1);
	pB1->signal_clicked().connect(sigc::ptr_fun(pB1_on_button_press_event));

	refBuilder->get_widget("button2", pB2);
	pB2->signal_clicked().connect(sigc::ptr_fun(pB2_on_button_press_event));

	refBuilder->get_widget("treeview1", pTrV1);
	pTrV1->set_events(Gdk::BUTTON_PRESS_MASK);	
	pTrV1->signal_button_press_event().connect(sigc::ptr_fun(pTrV1_on_button_press_event), false);
	
	refBuilder->get_widget("notebook1", pNB1);
	pNB1->signal_switch_page().connect(sigc::ptr_fun(pNB1_on_switch_page));

	refBuilder->get_widget("menu3", pM3);
	
	refBuilder->get_widget("textview1", pTeV1);
	
	refTreeModel = Gtk::ListStore::create(columns);
	
	pTrV1->set_model(refTreeModel);
	pTrV1->append_column_editable("Ось абсцисс", columns.columnX);
	pTrV1->append_column_editable("Ось ординат", columns.columnY);

	pSB1->push("Разместите точки на плоскости!");

	kit.run(*pWindow);

	return 0;
}

bool pTrV1_on_button_press_event(GdkEventButton* event)
{
	if(event->type == GDK_BUTTON_PRESS && event->button == 3)
		pM5->popup(event->button, event->time);

	return false;
}

void pB1_on_button_press_event ()
{
	refTreeModel->clear();
	pSB1->push(Glib::ustring("Список очищен от точек"));
}

void pB2_on_button_press_event ()
{
	
	pTrV1_save_list();
	
	std::ostringstream oss;
	
	for (size_t i = 0, size = points[currPoints].size(); i < size; ++i)
		oss << points[currPoints][i] << " - ";
		
	std::string sz = oss.str();

	if (sz.empty())
		sz = "В списке нет точек.";
	else
		sz.erase(sz.end() - 2);
	
	Glib::RefPtr < Gtk::TextBuffer > refTextBuffer = Gtk::TextBuffer::create();

	refTextBuffer->set_text(sz);
	pTeV1->set_buffer(refTextBuffer);

	pSB1->push(Glib::ustring("Список точек обработан"));
	
	pTrV1_update_list();
}

bool pMI7_on_button_press_event (GdkEventButton*)
{
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = pTrV1->get_selection();

	if(refSelection)
	{
		Gtk::TreeModel::iterator it = refSelection->get_selected();

		if(it)
			refTreeModel->erase(it);
			
		pSB1->push(Glib::ustring("Точка удалена из списка"));
	}

	return true;
}

bool pMI8_on_button_press_event (GdkEventButton*)
{
	Glib::RefPtr<Gtk::TreeView::Selection> refSelection = pTrV1->get_selection();

	if(refSelection)
	{
		Gtk::TreeModel::iterator it = refSelection->get_selected();
		Gtk::TreeModel::Row row;

		row = (it) ? *(refTreeModel->insert_after(it)) : *(refTreeModel->append());

		row[columns.columnX] = 0;
		row[columns.columnY] = 0;
		
		pSB1->push(Glib::ustring("Новая точка добавлена в список"));
	}

	return true;
}

void pTrV1_update_list ()
{
	if (!currPoints)
		return;

	refTreeModel->clear();

	for (size_t i = 0, size = points[currPoints].size(); i < size; ++i)
	{
		Gtk::TreeModel::Row row = *(refTreeModel->append());

		row[columns.columnX] = points[currPoints][i].x;
		row[columns.columnY] = points[currPoints][i].y;
	}
}

void pTrV1_save_list ()
{	
	if (!currPoints)
		return;

	points[currPoints].clear();

	typedef Gtk::TreeModel::Children tdTypeChildren;
	
	tdTypeChildren children = refTreeModel->children();

	for(tdTypeChildren::iterator it = children.begin(); it != children.end(); ++it)
	{
		Gtk::TreeModel::Row row = *it;

		points[currPoints].push(double(row[columns.columnX]), double(row[columns.columnY]));
	}
	
	pTrV1_update_list();
}

void pNB1_on_switch_page(GtkNotebookPage* page, guint pageNum)
{
	currPoints = pageNum;
	
	pSB1->push(Glib::ustring::compose("Выбран %1 режим ввода точек", currPoints ? "ручной" : "графический"));
	pTrV1_update_list();
}

void pAD1_on_about_dialog_response (int response)
{
	if (response == Gtk::RESPONSE_CLOSE || response == Gtk::RESPONSE_CANCEL)
		pAD1->hide();
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

		points[currPoints].correct(event->area.width, event->area.height);

		for (int i = 1, color = 0; i < points[currPoints].size(); ++i, color = (color + 1) % 2)
		{
			cr->set_source_rgba(0.7 + 0.2 * (float)color, 0.0, 0.0, 0.8);
			cr->move_to(points[currPoints][i - 1].x, points[currPoints][i - 1].y);
			cr->line_to(points[currPoints][i].x, points[currPoints][i].y);
			cr->stroke();
		}
		
		cr->set_line_width(9.0);
		
		for (size_t i = 0; i < points[currPoints].size(); ++i)
		{
			switch (points[currPoints][i].get_flag())
			{
				case CMARKEDPOINT_FLAG_NO_SELECT:
					cr->set_source_rgb(0.0, 0.0, 0.0);
					break;					
					
				case CMARKEDPOINT_FLAG_SELECT:
					cr->set_source_rgb(0.0, 0.0, 0.9);
					break;					
			}

			cr->begin_new_sub_path();
			cr->arc(points[currPoints][i].x, points[currPoints][i].y, 0.6, 0, 6.28);
			
			cr->stroke();
		}
	}

	return window;
}

bool pDA1_on_button_press_event (GdkEventButton * event)
{
	if (event->type == GDK_BUTTON_PRESS)
	{
		if (event->button == 1)
		{
			switch (points[currPoints].push(event->x, event->y, pDA1->get_width(), pDA1->get_height()))
			{
				case CPOINTS_PUSH_OK:		
					pSB1->push(Glib::ustring::compose("Точка #%1 добавлена на плоскость", points[currPoints].size()));
					break;
			
				case CPOINTS_PUSH_NO_SPACE:
					pSB1->push(Glib::ustring("Нельзя размещать точки так близко друг к другу"));
					break;				
			}
		}
	
		if (event->button == 3)
			if (size_t i = points[currPoints].search_click_point(event->x, event->y))
				points[currPoints][i - 1].set_flag((points[currPoints][i - 1].get_flag() == CMARKEDPOINT_FLAG_SELECT) ? CMARKEDPOINT_FLAG_NO_SELECT : CMARKEDPOINT_FLAG_SELECT);
			else
				pM3->popup(event->button, event->time);			
	}
	
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	
	return true;
}

bool pIMI6_on_button_press_event (GdkEventButton * event)
{
	points[currPoints].clear();
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());
	
	if (currPoints)
		pSB1->push("Список очищен от отчек ломаной");
	else
		pSB1->push("Плоскость очищена от точек ломаной");
		
	pTrV1_update_list();

	return true;
}

bool pIMI3_on_button_press_event (GdkEventButton * event)
{
	pAD1->run();

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
			if (points[currPoints].size())
			{
				Gtk::MessageDialog dialogM(*pWindow, "Объединить старые и новые координаты точек?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
				
				switch(dialogM.run())
				{
					case(Gtk::RESPONSE_YES):
					{
						switch (points[currPoints].push(newPoints))
						{
							case CPOINTS_PUSH_OK:				
								if (currPoints)
									pSB1->push(Glib::ustring("Все точки добавлены в список"));
								else
									pSB1->push(Glib::ustring("Все точки добавлены на плоскость"));
								break;
								
							case CPOINTS_PUSH_NOT_ALL:				
								if (currPoints)
									pSB1->push(Glib::ustring("Не все точки добавлены в список"));
								else
									pSB1->push(Glib::ustring("Не все точки добавлены на плоскость"));
								break;
						}
						break;
					}
					case(Gtk::RESPONSE_NO):
					{
						points[currPoints] = newPoints;
						break;
					}
				}
			}
			else
				points[currPoints] = newPoints;
			
			pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());			
		}
		else
		{
			Gtk::MessageDialog dialogM(*pWindow, "В файле нет точек", false, Gtk::MESSAGE_ERROR);
			dialogM.set_secondary_text("Проверьте правильность указания координат точек в файле.");
			dialogM.run();
		}
	}

	pTrV1_update_list();
	
	return true;
}

bool pIMI2_on_button_press_event (GdkEventButton * event)
{
	pTrV1_save_list();

	Gtk::FileChooserDialog dialogFC(*pWindow, "Выберите файл для сохранения координат точек", Gtk::FILE_CHOOSER_ACTION_SAVE);

	dialogFC.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dialogFC.add_button(Gtk::Stock::SAVE, Gtk::RESPONSE_OK);
	
	Gtk::FileFilter filter;
	filter.set_name("Текстовый файл");
	filter.add_pattern("*.txt");
	dialogFC.add_filter(filter);

	if (dialogFC.run() == Gtk::RESPONSE_OK)
		if (points[currPoints].save_to_file(dialogFC.get_filename()))
			pSB1->push(Glib::ustring::compose("Координаты точек сохранены в файл \"%1\" успешно", dialogFC.get_filename()));
		else
			pSB1->push(Glib::ustring::compose("Не удалось сохранить координаты точек в файл \"%1\"", dialogFC.get_filename()));

	return true;
}

bool pMI3_on_button_press_event (GdkEventButton * event)
{
	points[currPoints].mark_all_points(CMARKEDPOINT_FLAG_SELECT);

	pSB1->push(Glib::ustring("Выделены все точки ломаной"));
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());			

	return true;
}

bool pMI4_on_button_press_event (GdkEventButton * event)
{
	points[currPoints].mark_all_points(CMARKEDPOINT_FLAG_NO_SELECT);
	
	pSB1->push(Glib::ustring("Выделение со всех точек ломаной снято"));		
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());			

	return true;
}

bool pMI5_on_button_press_event (GdkEventButton * event)
{
	points[currPoints].delete_marked_points(CMARKEDPOINT_FLAG_SELECT);

	pSB1->push(Glib::ustring("Выделенные точки ломаной удалены"));		
	pDA1->queue_draw_area(0, 0, pDA1->get_width(), pDA1->get_height());			

	return true;
}
