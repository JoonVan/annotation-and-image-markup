#L
#  Copyright Northwestern University
#  Copyright Stanford University (ATB 1.0 and ATS 1.0)
#
#  Distributed under the OSI-approved BSD 3-Clause License.
#  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.

require 'prefs.ph';
require 'layout.ph';
require 'password.ph';
require 'lock.ph';
require 'write.ph';

$path_info=$ENV{'PATH_INFO'};

$aetitle = '';
$passwd = '';
if ($path_info ne '')
{
  ($dummy, $aetitle, $passwd, $rest) = split(/\//, $path_info);
}
if (($passwd eq '') || (! &checkurlcode($passwd, $aetitle)))
{
  # Password is incorrect.
  &page_title("Password invalid");
  printf("<A HREF=\"%s\">Click here</A> to return to main menu.\n", $prefs{'main.pl'});
  &page_footer;
} else {
  # Password is correct.
  &page_title("Station Data - '$aetitle'");
  printf("<TABLE BORDER CELLSPACING=1 WIDTH=100%>\n");
  printf("<TR><TD nowrap><B>Station Name</B></TD>\n");
  printf("<TD nowrap><B>Modality</B></TD>\n");
  printf("<TD nowrap><B>Application Entity</B></TD><TD></TD><TD></TD></TR>\n");

  &set_readlock("$prefs{'data_path'}/$aetitle");
  $filename = "$prefs{'data_path'}/$aetitle/$prefs{'datafile'}";
  &read_environment($filename);
  &release_lock;
  @keys = @STATION_KEYS;
  @values = ();
  for (@keys){ push(@values,join("\000",$STATION_VALUES{"$_\\name"},$_)); }
  for (sort(@values))
  {
    ($name, $key) = split(/\000/);
    printf("<TR><TD nowrap>%s</TD><TD nowrap>%s</TD><TD nowrap>%s</TD>",
      $name, $STATION_VALUES{"$key\\modality"}, $key);
    printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">update</A></TD>",
      $prefs{'statedit.pl'}, $aetitle, $passwd, unpack("H*",$key));
    printf("<TD nowrap><A HREF=\"%s/%s/%s/%s\">delete</A></TD></TR>\n",
      $prefs{'statdel.pl'}, $aetitle, $passwd, unpack("H*",$key));
  }
  printf("</TABLE><p>\n");
  printf("<A HREF=\"%s/%s/%s\">Create a new station</A><p>\n",
      $prefs{'statedit.pl'}, $aetitle, $passwd);
  printf("<A HREF=\"%s/%s/%s\">Back to main Menu</A>\n",
      $prefs{'main.pl'}, $aetitle, $passwd);
  &page_footer;
}