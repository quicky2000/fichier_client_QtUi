#ifndef _SEARCH_WIDGET_H_
#define _SEARCH_WIDGET_H_

#include <QLabel>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include <QHBoxLayout>

#include "client_list_table.h"
#include "achat_list_table.h"

class fichier_client;

//#include "fichier_client.h"

class search_widget : public QWidget
 {
     Q_OBJECT

 public:
   search_widget(fichier_client & p_fichier_client,QWidget * p_parent = NULL);

   void set_enable(bool p_enable);


 private slots:
     void criteria_modification();
     void client_selected(int row);
 private:
     QLineEdit * m_name_field;
     QLineEdit * m_first_name_field;
     QLineEdit * m_city_field;
     client_list_table *m_client_list_table;
     achat_list_table *m_achat_list_table;
     fichier_client & m_fichier_client;
 };

#endif
