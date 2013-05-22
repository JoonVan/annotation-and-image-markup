//L  
// Copyright Northwestern University
// Copyright Stanford University (ATB 1.0 and ATS 1.0)
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

using System.Collections.Generic;

using ClearCanvas.Common;
using ClearCanvas.Desktop.Configuration;
using ClearCanvas.ImageViewer.Common;

namespace AIM.Annotation.Configuration
{
	[ExtensionOf(typeof(ConfigurationPageProviderExtensionPoint))]
	class AimConfigurationPageProvider : IConfigurationPageProvider
	{
		public IEnumerable<IConfigurationPage> GetPages()
		{
            var listPages = new List<IConfigurationPage>();
            if (PermissionsHelper.IsInRole(ClearCanvas.ImageViewer.AuthorityTokens.ViewerVisible))
            {
                listPages.Add(new ConfigurationPage(AimConfigurationComponent.Path, new AimConfigurationComponent()));
                listPages.Add(new ConfigurationPage(AimMarkupColorComponent.Path, new AimMarkupColorComponent()));
            }
            return listPages.AsReadOnly();
		}
	}
}