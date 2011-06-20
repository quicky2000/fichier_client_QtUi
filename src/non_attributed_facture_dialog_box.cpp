
#include "non_attributed_facture_dialog_box.h"
#include "my_date_widget.h"
#include "facture.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <sstream>
#include <QMessageBox>

//------------------------------------------------------------------------------
non_attributed_facture_dialog_box::non_attributed_facture_dialog_box(QWidget * p_parent,std::vector<facture_status> & p_status_list,facture & p_facture):
  QDialog(p_parent),
  m_facture(p_facture),
  m_facture_reference_field(NULL),
  m_date_field(NULL),
  m_ok_button(NULL),
  m_cancel_button(NULL),
  m_status_field(NULL)
{
  setModal(true);
  // std::string l_title(p_facture.get_id() ? tr("Modification").toStdString() : tr("Creation").toStdString());
  //  l_title += tr(" of non attibuted_facture").toStdString();
  //  setTitle(l_title);
  QVBoxLayout *l_vertical_layout = new QVBoxLayout(this);
  QHBoxLayout *l_horizontal_layout = new QHBoxLayout();
  l_vertical_layout->addLayout(l_horizontal_layout);

  l_horizontal_layout->addWidget(new QLabel(tr("Facture reference")+" :"));

   m_facture_reference_field = new QLineEdit("");
   m_facture_reference_field->setInputMask("99");

   l_horizontal_layout->addWidget(m_facture_reference_field);

   l_horizontal_layout->addWidget(new QLabel(tr("Date")+" :"));

   m_date_field = new my_date_widget();
   l_horizontal_layout->addWidget(m_date_field);
   
   l_horizontal_layout->addWidget(new QLabel(tr("Status")+" :"));
   m_status_field = new QComboBox(this);
   
   std::vector<facture_status>::const_iterator l_iter = p_status_list.begin();
   std::vector<facture_status>::const_iterator l_iter_end = p_status_list.end();
   while(l_iter != l_iter_end)
     {
       m_status_field->addItem(l_iter->getName().c_str());
       m_status_ids.push_back(l_iter->get_id());
       ++l_iter;
     }
   l_horizontal_layout->addWidget(m_status_field);

   QHBoxLayout *l_button_layout = new QHBoxLayout();
   l_vertical_layout->addLayout(l_button_layout);

   m_ok_button = new QPushButton(tr("&Ok"));
   connect(m_ok_button,SIGNAL(clicked()),this,SLOT(accept()));
   l_button_layout->addWidget(m_ok_button);
 
   m_cancel_button = new QPushButton(tr("&Cancel"));
   connect(m_cancel_button,SIGNAL(clicked()),this,SLOT(reject()));
   l_button_layout->addWidget(m_cancel_button);

   if(p_facture.get_id())
     {
       std::stringstream l_facture_ref;
       l_facture_ref << p_facture.get_facture_ref();
       m_facture_reference_field->setText(l_facture_ref.str().c_str());
       m_date_field->set_iso_date(p_facture.get_date());
     }
}

//------------------------------------------------------------------------------
void non_attributed_facture_dialog_box::accept(void)
{
  std::cout << "Non attributed facture accept" << std::endl ;
  std::string l_ref_str = m_facture_reference_field->text().toStdString();
  bool l_valid = true;
  if(l_ref_str == "")
    {
      QMessageBox::warning(this,"Référence invalide",tr("La reference de facture est vide"), QMessageBox::Ok,QMessageBox::Ok);
      l_valid = false;
    }
  std::string l_date = m_date_field->get_iso_date();
  if(l_date.size() != 10)
    {
      l_valid = false;
      QMessageBox::warning(this,"Date invalide",tr("La date de facture est invalide"), QMessageBox::Ok,QMessageBox::Ok);
    }
  if(l_valid)
    {
      m_facture.set_facture_ref(strtol(l_ref_str.c_str(),NULL,10));
      m_facture.set_date(l_date);
      assert(m_status_field->currentIndex() < (int)m_status_ids.size());
      m_facture.set_status(m_status_ids[m_status_field->currentIndex()]);
      QDialog::accept();
    }
}

//------------------------------------------------------------------------------
void non_attributed_facture_dialog_box::reject(void)
{
  std::cout << "Non attributed facture reject" << std::endl ;
  QDialog::reject();
}
//EOF

