#ifndef CMODELCOLUMNS_H
#define CMODELCOLUMNS_H

#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treemodel.h>

class cModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
	cModelColumns()
	{
		add(columnX);
		add(columnY);
	}

	Gtk::TreeModelColumn < double > columnX;
	Gtk::TreeModelColumn < double > columnY;
};

#endif
