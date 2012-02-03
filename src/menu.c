/*
 *  menu.c
 *  This file is part of Leafpad
 *
 *  Copyright (C) 2004 Tarot Osuji
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <gdk/gdkkeysyms.h>
#include "leafpad.h"

static gchar *menu_translate(const gchar *path, gpointer data)
{
	gchar *retval;
	
	retval = (gchar *)_(path);
	return retval;
}

static GtkItemFactoryEntry menu_items[] =
{
	{ N_("/_File"), NULL,
		NULL, 0, "<Branch>" },
	{ N_("/File/_New"), "<control>N",
		G_CALLBACK(cb_file_new_window), 0, "<StockItem>", GTK_STOCK_NEW },
//	{ N_("/File/New _Window"), "<shift><control>N",
//		G_CALLBACK(cb_file_new), 1 },
	{ N_("/File/_Open..."), "<control>O",
		G_CALLBACK(cb_file_open), 0, "<StockItem>", GTK_STOCK_OPEN },
	{ N_("/File/_Save"), "<control>S",
		G_CALLBACK(cb_file_save), 0, "<StockItem>", GTK_STOCK_SAVE },
	{ N_("/File/Save _As..."), NULL,
		G_CALLBACK(cb_file_save_as), 0, "<StockItem>", GTK_STOCK_SAVE_AS },
	{ "/File/---", NULL,
		NULL, 0, "<Separator>" },
/*	{ N_("/File/Page Set_up..."), NULL,
		G_CALLBACK(cb_file_page_setup), 0 },
	{ N_("/File/_Print..."), "<control>P",
		G_CALLBACK(cb_file_print), 0, "<StockItem>", GTK_STOCK_PRINT },
	{ "/File/---", NULL,
		NULL, 0, "<Separator>" },
*/	{ N_("/File/_Quit"), "<control>Q",
		G_CALLBACK(cb_file_quit), 0, "<StockItem>", GTK_STOCK_QUIT },
	{ N_("/_Edit"),	 NULL,
		NULL, 0, "<Branch>" },
	{ N_("/Edit/_Undo"), "<control>Z",
		G_CALLBACK(cb_edit_undo), 0, "<StockItem>", GTK_STOCK_UNDO },
	{ N_("/Edit/_Redo"), "<control>Y",
		G_CALLBACK(cb_edit_redo), 0, "<StockItem>", GTK_STOCK_REDO },
	{ "/Edit/---", NULL,
		NULL, 0, "<Separator>" },
	{ N_("/Edit/Cu_t"), "<control>X",
		G_CALLBACK(cb_edit_cut), 0, "<StockItem>", GTK_STOCK_CUT },
	{ N_("/Edit/_Copy"), "<control>C",
		G_CALLBACK(cb_edit_copy), 0, "<StockItem>", GTK_STOCK_COPY },
	{ N_("/Edit/_Paste"), "<control>V",
		G_CALLBACK(cb_edit_paste), 0, "<StockItem>", GTK_STOCK_PASTE },
	{ N_("/Edit/_Delete"), NULL,
		G_CALLBACK(cb_edit_delete), 0, "<StockItem>", GTK_STOCK_DELETE },
	{ "/Edit/---", NULL,
		NULL, 0, "<Separator>" },
	{ N_("/Edit/Select _All"), "<control>A",
		G_CALLBACK(cb_edit_select_all), 0 },
	{ N_("/_Search"),	 NULL,
		NULL, 0, "<Branch>" },
	{ N_("/Search/_Find..."), "<control>F",
		G_CALLBACK(cb_search_find), 0, "<StockItem>", GTK_STOCK_FIND },
	{ N_("/Search/Find _Next"), "F3",
		G_CALLBACK(cb_search_find_next), 0 },
	{ N_("/Search/Find _Previous"), "<shift>F3",
		G_CALLBACK(cb_search_find_prev), 0 },
	{ N_("/Search/_Replace..."), "<control>H",
		G_CALLBACK(cb_search_replace), 0, "<StockItem>", GTK_STOCK_FIND_AND_REPLACE },
	{ "/Search/---", NULL,
		NULL, 0, "<Separator>" },
	{ N_("/Search/_Jump To..."), "<control>J",
		G_CALLBACK(cb_search_jump_to), 0, "<StockItem>", GTK_STOCK_JUMP_TO },
	{ N_("/_Options"), NULL,
		NULL, 0, "<Branch>" },
	{ N_("/Options/_Font..."), NULL,
		G_CALLBACK(cb_option_font), 0, "<StockItem>", GTK_STOCK_SELECT_FONT },
	{ N_("/Options/_Word Wrap"), NULL,
		G_CALLBACK(cb_option_word_wrap), 0, "<CheckItem>" },
	{ N_("/Options/_Line Numbers"), NULL,
		G_CALLBACK(cb_option_line_numbers), 0, "<CheckItem>" },
	{ "/Options/---", NULL,
		NULL, 0, "<Separator>" },
	{ N_("/Options/_Auto Indent"), NULL,
		G_CALLBACK(cb_option_auto_indent), 0, "<CheckItem>" },
	{ N_("/_Help"), NULL,
		NULL, 0, "<Branch>" },
	{ N_("/Help/_About"), "F1",
		G_CALLBACK(cb_help_about), 0, "<StockItem>", GTK_STOCK_HELP },
};

static gint nmenu_items = sizeof(menu_items) / sizeof(GtkItemFactoryEntry);

GtkWidget *create_menu_bar(GtkWidget *window, gpointer data)
{
	GtkAccelGroup *accel_group;
	GtkItemFactory *ifactory;
	
	accel_group = gtk_accel_group_new();
	ifactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR, "<main>", accel_group);
	gtk_item_factory_set_translate_func(ifactory, menu_translate, NULL, NULL);
	gtk_item_factory_create_items(ifactory, nmenu_items, menu_items, data);
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);
	
	/* hidden keybinds */
	gtk_accel_group_connect(
		accel_group, GDK_W, GDK_CONTROL_MASK, 0,
		g_cclosure_new_swap(G_CALLBACK(cb_file_new), data, NULL));
/*	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/File/New"),
		"activate", accel_group, GDK_W, GDK_CONTROL_MASK, 0); */
	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/File/Save As..."),
		"activate", accel_group, GDK_S, GDK_SHIFT_MASK | GDK_CONTROL_MASK, 0);
/*	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "<main>/File/Quit"),
		"activate", accel_group, GDK_Escape, 0, 0); */
	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/Edit/Redo"),
		"activate", accel_group, GDK_Z, GDK_SHIFT_MASK | GDK_CONTROL_MASK, 0);
	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/Search/Find Next"),
		"activate", accel_group, GDK_G, GDK_CONTROL_MASK, 0);
	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/Search/Find Previous"),
		"activate", accel_group, GDK_G, GDK_SHIFT_MASK | GDK_CONTROL_MASK, 0);
	gtk_widget_add_accelerator(
		gtk_item_factory_get_widget(ifactory, "/Search/Replace..."),
		"activate", accel_group, GDK_R, GDK_CONTROL_MASK, 0);
	
	/* planned functions */
/*	gtk_widget_set_sensitive(
		gtk_item_factory_get_widget(ifactory, "<main>/Options/Auto Indent"),
		FALSE);
	gtk_item_factory_delete_item(ifactory, "/Options/Auto Indent"); */
//	gtk_item_factory_delete_item(ifactory, "/File/New Window");
	
	return gtk_item_factory_get_widget(ifactory, "<main>");
}
