#ifndef vtkSZ3Reader_h
#define vtkSZ3Reader_h

#include "vtkDataReader.h"
#include "vtkDataObjectAlgorithm.h"
#include "vtkImageAlgorithm.h"

#include <string>

class VTKSZ3READER_EXPORT vtkSZ3Reader : public vtkImageAlgorithm
{
public:
  static vtkSZ3Reader* New();
  vtkTypeMacro(vtkSZ3Reader, vtkImageAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  void SetDomainDimensions(int x, int y, int z);
  void GetDomainDimensions(int& x, int& y, int& z);

  void SetDataType(const std::string& type);
  std::string GetDataType() const;

protected:
  vtkSZ3Reader();
  ~vtkSZ3Reader();
  int RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector*);
  int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*);

  char* FileName;
  int DomainDimensions[3];
  std::string DataType;

private:
  vtkSZ3Reader(const vtkSZ3Reader&);
  void operator=(const vtkSZ3Reader&);
};

#endif
