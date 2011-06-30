#ifndef _LIVRE_FACTURE_WIDGET_H_
#define _LIVRE_FACTURE_WIDGET_H_

#include <QWidget>
#include <stdint.h>
#include "facture_status.h"

class QPushButton;
class QLineEdit;

class fichier_client;
class livre_facture_table;
class livre_facture;
class my_date_widget;
class base_facture_widget;
class facture_client_list_table;

class livre_facture_widget : public QWidget
 {
     Q_OBJECT

 public:
   livre_facture_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
   void set_enable(bool p_enable);
   void set_facture_creation_enabled(bool p_enabled);
   void set_delete_livre_facture_enabled(bool p_enabled);
   void set_modify_livre_facture_enabled(bool p_enabled);
   void refresh_list_facture_of_livre_facture(void);
   void set_allowed_facture_references(const std::vector<uint32_t> & p_remaining_refs);
   void set_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
   void set_status_list(const std::vector<facture_status> & p_status_list);
   const std::string get_non_attributed_facture_date(void)const;
   uint32_t get_non_attributed_facture_livre_facture_id(void)const;
   uint32_t get_non_attributed_facture_reference(void)const;
   const facture_status * get_non_attributed_facture_status(void)const;
   void clear_non_attributed_facture_date(void);
   void enable_non_attributed_facture_fields(bool p_enable);
   bool is_non_attributed_facture_date_complete(void)const;
   bool is_non_attributed_facture_date_empty(void)const;
 private slots:
   //Livre facture fields events
   void criteria_modification(void);
   void content_modification(void);
   // Livre facture button events
   void create_livre_facture(void);
   void delete_livre_facture(void);
   void modify_livre_facture(void);
   // Livre facture table events
   void livre_facture_selected(int row);
   void livre_facture_selection_changed(void);
   // Non attributed facture button events
   void create_facture(void);
   void delete_facture(void);
   void modify_facture(void);
   // Non attributed facture table events
   void facture_selected(int row);
   void facture_selection_changed(void);
   // Non attributed facture fields events
   void non_attributed_facture_date_entered(void);
   void non_attributed_facture_ref_selected(void);
   void non_attributed_facture_status_selected(void);
   void non_attributed_facture_livre_facture_selected(void);
 private:
     void clear_text_fields(void);
     uint32_t get_selected_livre_facture_id(void);
     void get_selected_livre_facture(livre_facture & p_selected);

     QPushButton * m_create_livre_facture_button;
     QPushButton * m_delete_livre_facture_button;
     QPushButton * m_modify_livre_facture_button;
     QLineEdit * m_livre_id_field;
     my_date_widget * m_start_date_field;
     my_date_widget * m_end_date_field;
     livre_facture_table *m_livre_facture_table;
     // Facture related part
     QPushButton * m_create_facture_button;
     QPushButton * m_delete_facture_button;
     QPushButton * m_modify_facture_button;
     base_facture_widget * m_base_facture_widget;
     facture_client_list_table *m_facture_client_list_table;
     fichier_client & m_fichier_client;
 };

#endif
