#ifndef _FACTURE_STATUS_WIDGET_H_
#define _FACTURE_STATUS_WIDGET_H_

#include <QWidget>
#include <stdint.h>

class QPushButton;
class QLineEdit;

class fichier_client;
class facture_status_list_table;
class facture_status;

class facture_status_widget : public QWidget
 {
     Q_OBJECT

 public:
   facture_status_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);
   void set_enable(bool p_enable);

 private slots:
   void criteria_modification(void);
   void create_facture_status(void);
   void delete_facture_status(void);
   void modify_facture_status(void);
   void facture_status_selected(int row);
   void facture_status_selection_changed(void);
 private:
   void clear_text_fields(void);
   uint32_t get_selected_facture_status_id(void);
   void get_selected_facture_status(facture_status & p_selected);

   bool m_modif_pending;
   QPushButton * m_create_facture_status_button;
   QPushButton * m_delete_facture_status_button;
   QPushButton * m_modify_facture_status_button;
   QLineEdit * m_status_name_field;
   facture_status_list_table *m_facture_status_list_table;
   fichier_client & m_fichier_client;
 };

#endif
