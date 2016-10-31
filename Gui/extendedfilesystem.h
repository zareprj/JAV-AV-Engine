#ifndef EXTENDEDFILESYSTEM_H
#define EXTENDEDFILESYSTEM_H

#include <QFileSystemModel>
#include <QVectorIterator>
#include <QDir>
#include <QDebug>




class ExtendedFileSystem : public QFileSystemModel
{
 Q_OBJECT
public:
	ExtendedFileSystem();
	virtual int columnCount  ( const QModelIndex & parent = QModelIndex() ) const ;
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
	virtual QVariant	data ( const QModelIndex & index, int role = Qt::DisplayRole ) const;
	virtual Qt::ItemFlags	flags ( const QModelIndex & index ) const;
	virtual bool	setData ( const QModelIndex & idx, const QVariant & value, int role = Qt::EditRole );
	QVector<QModelIndex> m_vchanged;
	QVector<QModelIndex> m_Partially;

protected:
    virtual bool	event ( QEvent * event );

private :
	bool RemoveCheked(QModelIndex const & index);
	bool Removeparirity(QModelIndex const & index);



};

#endif EXTENDEDFILESYSTEM_H
