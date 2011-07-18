#ifndef _BASE_FACTURE_WIDGET_H_
#define _BASE_FACTURE_WIDGET_H_

#include "facture_status.h"

#include <inttypes.h>
#include <QWidget>
#include <vector>

class QWidget;
class QComboBox;
class QHBoxLayout;
class my_date_widget;

class base_facture_widget: public QWidget
{
  Q_OBJECT
    public:
  base_facture_widget(QWidget * p_parent);

  void set_date(const std::string &p_date);
  void set_enabled(bool p_enabled);
  void set_allowed_facture_ref(const std::vector<uint32_t> & p_list);
  void set_reference(uint32_t p_ref);
  void set_allowed_livre_ids(const std::vector<uint32_t> & p_livre_ids);
  void set_livre_id(uint32_t p_id);
  void set_status_list(const std::vector<facture_status> & p_status_list);
  void set_status(uint32_t p_id);

  bool is_date_complete(void)const;
  bool is_date_empty(void)const;
  const std::string get_iso_date(void)const;
  uint32_t get_facture_reference(void)const;
  uint32_t get_livre_facture_id(void)const;
  const facture_status * get_facture_status(void)const;

  void clear_date(void);

  private slots:
  void date_entered(void);
  void facture_ref_selected(int);
  void livre_facture_selected(int);
  void status_selected(int);

 signals:
  void new_date_entered(void);
  void new_facture_ref_selected(void);
  void new_livre_facture_selected(void);
  void new_status_selected(void);
  
 protected:
  QHBoxLayout * get_layout(void);
  void set_combo_box_content(QComboBox * p_combo_box,std::vector<uint32_t> & p_current, const std::vector<uint32_t> & p_list);

 private:
  uint32_t get_livre_facture_id(int p_index)const;
  uint32_t get_facture_reference(int p_index)const;
  const facture_status * get_facture_status(int p_index)const;

  QHBoxLayout * m_layout;
  my_date_widget * m_date_field;
  QComboBox * m_livre_facture_id_field;
  QComboBox * m_facture_reference_field;
  QComboBox * m_status_field;
  std::vector<uint32_t> m_livre_facture_ids;
  std::vector<uint32_t> m_facture_references;
  std::vector<facture_status> m_status;
};
#endif
