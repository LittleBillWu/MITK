/*============================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center (DKFZ)
All rights reserved.

Use of this source code is governed by a 3-clause BSD license that can be
found in the LICENSE file.

============================================================================*/


#ifndef QmitkDataGenerationJobBase_h
#define QmitkDataGenerationJobBase_h


//QT
#include <QRunnable>
#include <QObject>
#include <QMetaType>

//MITK
#include <mitkBaseData.h>

#include <MitkImageStatisticsUIExports.h>

/*!
\brief QmitkDataGenerationJobBase
Base class for generation jobs used by QmitkDataGenerationBase and derived classes.
*/
class MITKIMAGESTATISTICSUI_EXPORT QmitkDataGenerationJobBase : public QObject, public QRunnable
{
    Q_OBJECT

public:
  /** Result map that indicates all results generated by the job.
   The key is a job specific label for the results.*/
  using ResultMapType = std::map<std::string, mitk::BaseData::Pointer>;

  virtual ResultMapType GetResults() const = 0;

  /** Calls RunComputation() and takes care of the error handling and result signalling.*/
  void run() final;

  /*!
  /brief Returns a flag the indicates if the job computation was successful.*/
  bool GetComputationSuccessFlag() const;

  std::string GetLastErrorMessage() const;

  bool IsRunning() const;

signals:
    void Error(QString err, const QmitkDataGenerationJobBase* job);
    /*! @brief Signal is emitted when results are available. 
    @param results produced by the job and ready to be used.
    @param job the job that produced the data
    */
    void ResultsAvailable(ResultMapType results, const QmitkDataGenerationJobBase* job);
    
protected:
  QmitkDataGenerationJobBase() = default;

  virtual ~QmitkDataGenerationJobBase() = default;

  /**Does the real computation. Returns true if there where results produced.*/
  virtual bool RunComputation() = 0;

  std::string m_LastErrorMessage;

private:
  bool m_ComputationSuccessful = false;
  bool m_IsRunning = false;
};

#endif
