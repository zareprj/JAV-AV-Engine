#ifndef ExtendedFileSystem_CPP
#define ExtendedFileSystem_CPP

#include "extendedfilesystem.h"
void signalWaitForInit();
int m_iNumRowsLevel1;
ExtendedFileSystem::ExtendedFileSystem()
{
	m_iNumRowsLevel1=0;
}
//////////////////////////////////////////////////////////
int ExtendedFileSystem::columnCount ( const QModelIndex & parent ) const
 {
    return QFileSystemModel::columnCount(parent)-3;
 }

int ExtendedFileSystem::rowCount(const QModelIndex &parent) const
{
	int rowCount=QFileSystemModel::rowCount(parent);
	if (!parent.isValid())
	{
		m_iNumRowsLevel1=rowCount;//emit setRowCountLevel1(rowCount);
	}
	return rowCount;	
}

///////////////////////////////////////////////

QVariant ExtendedFileSystem::data ( const QModelIndex & index, int role ) const
{
    QModelIndex TempIndex ;
	if(!index.parent().isValid() && index.row()==m_iNumRowsLevel1-1 && role == Qt::DisplayRole)
	{
		signalWaitForInit();
	} 
    if (role == 10 && index.column() == 0 )
    {
        QVector<QModelIndex >::iterator  it;
        for ( it = (QModelIndex *) m_vchanged.begin() ; it != m_vchanged.end() ; it++)
        {
            TempIndex = index;
            do
            {
                if ((*it) == TempIndex)
                {
                    return QVariant(Qt::Checked);
                }

                TempIndex = TempIndex.parent();
            }while (TempIndex.isValid());

        }
        for (it = (QModelIndex *) m_Partially.begin() ; it != m_Partially.end() ; it++)
        {

            if((*it).internalId()==index.internalId())
            {
                return QVariant(Qt::PartiallyChecked);
            }
        }
		 
        return QVariant(Qt::Unchecked);
    }

    return QFileSystemModel::data(index , role);

}

/////////////////////////////////////
Qt::ItemFlags ExtendedFileSystem::flags ( const QModelIndex & index ) const
{
    if (index.column()==0)
    {
        return  Qt::ItemIsUserCheckable | Qt::ItemIsSelectable |Qt::ItemIsEditable| Qt::ItemIsEnabled | Qt::ItemIsTristate;

    }
       return QFileSystemModel::flags(index) ;
}

////////////////////////////////////////////////////////////////////
bool	ExtendedFileSystem::setData ( const QModelIndex & idx, const QVariant & value, int role  )
{
    if (idx.column()  == 0 && role == 10 )
    {
        if ( value.toInt() == 2 )
        {
            QVector<QModelIndex >::iterator  it;
            for ( it = m_vchanged.begin() ; it != m_vchanged.end() ; it++)
            {
                if (!(*it).isValid())
                {
                    continue ;
                }
               QModelIndex TempIndex = (*it).parent();
                while (TempIndex.isValid())
                {
                    if (TempIndex.internalId() == (idx).internalId())
                    {
                        QVector<QModelIndex >::iterator  tempit = it - 1;
                        m_vchanged.erase(it);
                        it = tempit ;
                    }

                    TempIndex = TempIndex.parent();
                }

                /*if ((*it) == index.internalId() || (*it) == index.parent().internalId())
                {

                     return QVariant(Qt::Checked);
                }*/
            }


            for ( it = m_Partially.begin() ; it != m_Partially.end() ; it++)
            {
                if (!(*it).isValid())
                {
                    continue ;
                }
                if ((*it).internalId()==idx.internalId())
                {
                    QVector<QModelIndex >::iterator  tempit = it - 1;
                    m_Partially.erase(it);
                    it = tempit ;
                    continue;
                }
               QModelIndex TempIndex = (*it).parent();
                while (TempIndex.isValid())
                {
                    if (TempIndex.internalId() == (idx).internalId())
                    {
                        QVector<QModelIndex >::iterator  tempit = it - 1;
                        m_Partially.erase(it);
                        it = tempit ;
                    }

                    TempIndex = TempIndex.parent();
                }

            }

            QModelIndex TempIndex = idx.parent();
            while (TempIndex.isValid())
            {
                bool existFlag = false;
                for ( it = m_Partially.begin() ; it != m_Partially.end() ; it++)
                {
                    if (!(*it).isValid())
                    {
                        continue ;

                    }
                    if ((*it).internalId() == TempIndex.internalId() )
                    {
                        existFlag = true ;
                        break ;
                    }
                }
                if (existFlag == false)
                {
                    m_Partially.push_back(TempIndex);
                    TempIndex = TempIndex.parent();
                }
                else
                {
                    break ;
                }
            }
            m_vchanged.push_back(idx);

        }
        else
        {
            RemoveCheked(idx );

        }
        emit dataChanged(idx.child(0,0),idx.child(0,1));
        return true;
    }
    return QFileSystemModel::setData(idx,value,role);
}

//////////////////////////////////////////////////////////////
bool	ExtendedFileSystem::event ( QEvent * event )
{
    return QFileSystemModel::event(event);
}
// QVariant ExtendedFileSystem::headerData(int section, Qt::Orientation orientation, int role)
//{

//}

////////////////////////////////////////////////////////////////
bool ExtendedFileSystem::RemoveCheked(QModelIndex const & index )
{
    if (!index.isValid())
    {
        return false ;
    }
    QVector<QModelIndex >::iterator it;
    for ( it =  m_vchanged.begin() ; it != m_vchanged.end() ; it++)
    {
        if ((*it).internalId() == index.internalId())
        {
            Removeparirity((*it));
            m_vchanged.erase(it);
            return true ;
        }
    }
 RemoveCheked(index.parent());

 bool existFlag= false;
   for (int i = 0 ; i< index.row() ;i++)
    {
        existFlag=true;
       m_vchanged.push_back(index.sibling(i , index.column()));
    }

    QModelIndex childtemp=index.sibling(index.row()+1,index.column());

    while (childtemp.isValid())
    {
        existFlag=true;
        m_vchanged.push_back(childtemp);
        childtemp= childtemp.sibling(childtemp.row()+1 ,childtemp.column());
    }
    if (existFlag==true )
    {
        m_Partially.push_back(index.parent());
    }
return existFlag;
}

/////////////////////////////////////////////////////////////////////

bool ExtendedFileSystem::Removeparirity(QModelIndex const & index)
{
    if (!index.isValid())
    {
        return false ;
    }
    for (int i = 0 ; i< index.row() ;i++)
    {
         QVector<QModelIndex >::iterator  it;
         for ( it = m_Partially.begin() ; it != m_Partially.end() ; it++)
         {
             if ((*it).internalId() == index.sibling(i , index.column()).internalId())
             {
                 return true ;
             }
          }
          for ( it = m_vchanged.begin() ; it != m_vchanged.end() ; it++)
          {
            if ((*it).internalId() == index.sibling(i , index.column()).internalId())
            {
                return true ;
            }

           }
    }

     QModelIndex childtemp=index.sibling(index.row()+1,index.column());

     while (childtemp.isValid())
     {
         QVector<QModelIndex >::iterator  it;
         for ( it = m_Partially.begin() ; it != m_Partially.end() ; it++)
         {
             if ((*it).internalId() == childtemp.internalId())
             {
                 return true ;
             }
          }
          for ( it = m_vchanged.begin() ; it != m_vchanged.end() ; it++)
          {
            if ((*it).internalId() == childtemp.internalId())
            {
                return true ;
            }

           }
          childtemp= childtemp.sibling(childtemp.row()+1 ,childtemp.column());
     }
     QVector<QModelIndex >::iterator  it;
     for ( it = m_Partially.begin() ; it != m_Partially.end() ; it++)
     {
         if ((*it).internalId() == index.parent().internalId())
         {
             QVector<QModelIndex >::iterator  tempit = it - 1;
             m_Partially.erase(it);
             it = tempit ;
             break ;
         }
      }
    return  Removeparirity(index.parent()) ;
}
#endif ExtendedFileSystem_CPP