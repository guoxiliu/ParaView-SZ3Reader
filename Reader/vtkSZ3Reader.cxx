#include "vtkSZ3Reader.h"

#include "vtkCellData.h"
#include "vtkDataArray.h"
#include "vtkFloatArray.h"
#include "vtkImageAlgorithm.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPVInformationKeys.h"
#include "vtkPointData.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <iostream>

vtkStandardNewMacro(vtkSZ3Reader);

vtkSZ3Reader::vtkSZ3Reader()
{
  this->FileName = nullptr;
  this->DomainDimensions[0] = 0;
  this->DomainDimensions[1] = 0;
  this->DomainDimensions[2] = 0;
  this->DataType = "Float32";
  this->SetNumberOfInputPorts(0);
  this->SetNumberOfOutputPorts(1);
}

vtkSZ3Reader::~vtkSZ3Reader()
{
  this->SetFileName(nullptr);
}

void vtkSZ3Reader::SetDomainDimensions(int x, int y, int z)
{
  this->DomainDimensions[0] = x;
  this->DomainDimensions[1] = y;
  this->DomainDimensions[2] = z;
  this->Modified();
}

void vtkSZ3Reader::GetDomainDimensions(int& x, int& y, int& z)
{
  x = this->DomainDimensions[0];
  y = this->DomainDimensions[1];
  z = this->DomainDimensions[2];
}

void vtkSZ3Reader::SetDataType(const std::string& type)
{
  this->DataType = type;
  this->Modified();
}

std::string vtkSZ3Reader::GetDataType() const
{
  return this->DataType;
}

int vtkSZ3Reader::RequestData(
  vtkInformation* /*request*/, vtkInformationVector** /*inputVector*/, vtkInformationVector* outputVector)
{
  vtkImageData* output = vtkImageData::GetData(outputVector);
  std::cout << "Hello World from vtkSZ3Reader!" << std::endl;
  std::cout << "FileName: " << (this->FileName ? this->FileName : "(none)") << std::endl;
  std::cout << "DomainDimensions: " << this->DomainDimensions[0] << ", " << this->DomainDimensions[1] << ", " << this->DomainDimensions[2] << std::endl;
  std::cout << "DataType: " << this->DataType << std::endl;

  output->SetDimensions(1, 1, 1);
  output->AllocateScalars(VTK_FLOAT, 1);
  float* pixel = static_cast<float*>(output->GetScalarPointer());
  pixel[0] = 42.0f;
  return 1;
}

int vtkSZ3Reader::RequestInformation(
    vtkInformation* /*request*/, 
    vtkInformationVector** /*inputVector*/, 
    vtkInformationVector* outputVector)
{
  vtkInformation* outInfo = outputVector->GetInformationObject(0);

  // Set the whole extent based on DomainDimensions
  int extent[6] = {0, 0, 0, 0, 0, 0};
  extent[1] = this->DomainDimensions[0] > 0 ? this->DomainDimensions[0] - 1 : 0;
  extent[3] = this->DomainDimensions[1] > 0 ? this->DomainDimensions[1] - 1 : 0;
  extent[5] = this->DomainDimensions[2] > 0 ? this->DomainDimensions[2] - 1 : 0;
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(), extent, 6);

  // Set default origin and spacing
  double origin[3] = {0.0, 0.0, 0.0};
  double spacing[3] = {1.0, 1.0, 1.0};
  outInfo->Set(vtkDataObject::ORIGIN(), origin, 3);
  outInfo->Set(vtkDataObject::SPACING(), spacing, 3);

  return 1;
}

int vtkBDATReader::RequestInformation(
    vtkInformation*, 
    vtkInformationVector**, 
    vtkInformationVector* outVec)
{
  
  return 1;
}

void vtkSZ3Reader::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "FileName: " << (this->FileName ? this->FileName : "(none)") << "\n";
  os << indent << "DomainDimensions: " << this->DomainDimensions[0] << ", " << this->DomainDimensions[1] << ", " << this->DomainDimensions[2] << "\n";
  os << indent << "DataType: " << this->DataType << "\n";
}
