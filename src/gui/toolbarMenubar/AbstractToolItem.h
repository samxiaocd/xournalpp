/*
 * Xournal++
 *
 * Part of the customizable toolbars
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __ABSTRACTTOOLITEM_H__
#define __ABSTRACTTOOLITEM_H__

#include "AbstractItem.h"

class AbstractToolItem: public AbstractItem {
public:
	AbstractToolItem(String id, ActionHandler * handler, ActionType type, GtkWidget * menuitem = NULL);
	virtual ~AbstractToolItem();

	virtual void selected(ActionGroup group, ActionType action);
	static void toolButtonCallback(GtkToolButton *toolbutton, AbstractToolItem * item);
	virtual GtkToolItem * createItem(bool horizontal);
	void setPopupMenu(GtkWidget * popupMenu);
	GtkWidget * getPopupMenu();

	bool isUsed();
	void setUsed(bool used);

protected:
	virtual GtkToolItem * newItem() = 0;

	virtual void enable(bool enabled);

private:
	XOJ_TYPE_ATTRIB;

protected:
	GtkToolItem * item;
	GtkWidget * popupMenu;

	bool used;
};

#endif /* __ABSTRACTTOOLITEM_H__ */