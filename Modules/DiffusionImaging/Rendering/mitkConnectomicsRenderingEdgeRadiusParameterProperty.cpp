/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "mitkConnectomicsRenderingEdgeRadiusParameterProperty.h"
#include "mitkConnectomicsRenderingProperties.h"

#define EDGE_RADIUS_CONSTANT 0

mitk::ConnectomicsRenderingEdgeRadiusParameterProperty::ConnectomicsRenderingEdgeRadiusParameterProperty( )
{
  AddRenderingEdgeRadiusParameters();
  SetValue( EDGE_RADIUS_CONSTANT );
}


mitk::ConnectomicsRenderingEdgeRadiusParameterProperty::ConnectomicsRenderingEdgeRadiusParameterProperty( const IdType& value )
{
  AddRenderingEdgeRadiusParameters();
  if ( IsValidEnumerationValue( value ) )
  {
    SetValue( value ) ;
  }
  else
  {
    SetValue( EDGE_RADIUS_CONSTANT );
  }
}

mitk::ConnectomicsRenderingEdgeRadiusParameterProperty::ConnectomicsRenderingEdgeRadiusParameterProperty( const std::string& value )
{
  AddRenderingEdgeRadiusParameters();
  if ( IsValidEnumerationValue( value ) )
  {
    SetValue( value );
  }
  else
  {
    SetValue( EDGE_RADIUS_CONSTANT );
  }
}



void mitk::ConnectomicsRenderingEdgeRadiusParameterProperty::AddRenderingEdgeRadiusParameters()
{
  AddEnum( connectomicsRenderingEdgeParameterConstant , EDGE_RADIUS_CONSTANT );
}


bool mitk::ConnectomicsRenderingEdgeRadiusParameterProperty::AddEnum( const std::string& name, const IdType& id )
{
  return Superclass::AddEnum( name, id );
}
