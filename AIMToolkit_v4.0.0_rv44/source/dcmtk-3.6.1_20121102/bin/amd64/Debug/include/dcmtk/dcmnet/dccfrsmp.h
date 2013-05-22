/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#ifndef DCCFRSMP_H
#define DCCFRSMP_H

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/oflist.h"   /* for class OFList<> */
#include "dcmtk/ofstd/ofcond.h"   /* for class OFCondition */
#include "dcmtk/dcmnet/dcmsmap.h"  /* for class DcmSimpleMap<> */
#include "dcmtk/dcmnet/dccfuidh.h" /* for class DcmUIDHandler */
#include "dcmtk/dcmnet/assoc.h"    /* for T_ASC_SC_ROLE */

class DcmPresentationContextMap;

/** this helper class is a role selection list entry.
 *  Not intended for use by the end user.
 */
class DCMTK_DCMNET_EXPORT DcmRoleSelectionItem
{
public:
  /** constructor
   *  @param role supported SCP/SCU role
   *  @param abstractSyntax abstract syntax
   */
  DcmRoleSelectionItem(
    T_ASC_SC_ROLE role,
    const DcmUIDHandler& abstractSyntax );

  /// copy constructor
  DcmRoleSelectionItem(const DcmRoleSelectionItem& arg);
 
  /// destructor
  ~DcmRoleSelectionItem();

  /// assignment operator
  DcmRoleSelectionItem& operator=(const DcmRoleSelectionItem& arg);

  /** checks if the given argument matches the abstract syntax UID
   *  maintained by this object
   *  @param arg argument to compare to
   *  @return true if equal, false otherwise
   */
  OFBool matches(const DcmUIDHandler& arg) const
  {
    return arg == uid_;
  }

  /** returns a const reference to the abstract syntax UID
   *  maintained by this object
   *  @return reference to abstract syntax UID
   */   
  const DcmUIDHandler& getAbstractSyntax() const
  {
    return uid_;
  }

  /** returns the role maintained by this object
   */
  T_ASC_SC_ROLE getRole() const
  {
    return role_;
  } 

  /** comparison operator.
   *  @param arg object to compare with
   *  @return true if equal
   */
  OFBool operator==(const DcmRoleSelectionItem& arg) const
  {
    return (role_ == arg.role_) && (uid_ == arg.uid_); 
  }

private:

  /// SCP/SCU role
  T_ASC_SC_ROLE role_;

  /// abstract syntax
  DcmUIDHandler uid_;
};


/** this helper class is a simple list of role selection list entries.
 *  Not intended for use by the end user.
 */
typedef OFList<DcmRoleSelectionItem> DcmRoleSelectionList;

/** this helper class maintains a map of role selection lists.
 *  Not intended for use by the end user.
 */
class DCMTK_DCMNET_EXPORT DcmRoleSelectionMap
{
public:
  /// constructor
  DcmRoleSelectionMap();

  /// destructor
  ~DcmRoleSelectionMap();

  /** add new entry to list within map.
   *  If key is new, new list is created. Otherwise value
   *  is appended to existing list.
   *  @param key map key
   *  @param abstractSyntaxUID abstract syntax UID
   *  @param role SCP/SCU role
   *  @return EC_Normal if successful, an error code otherwise
   */
  OFCondition add(
    const char *key,
    const char *abstractSyntaxUID,
    T_ASC_SC_ROLE role);

  /** checks if the key is known
   *  @param key key name, must not be NULL
   *  @return true if key is known, false otherwise
   */
  OFBool isKnownKey(const char *key) const;

  /** checks if each abstract syntax in the role selection list
   *  identified by key is also contained in the presentation context
   *  list identified by pckey and maintained by pclist.
   *  @param key role selection key to check
   *  @param pclist map of presentation context lists
   *  @param pckey presentation context list key to check against
   *  @return EC_Normal if consistent, an error code otherwise
   */
  OFCondition checkConsistency(
    const char *key, 
    const DcmPresentationContextMap& pclist,
    const char *pckey) const;

  /** returns the list of role selection items identified by the given key
   *  @param key role selection list to search
   *  @return pointer to role selection list if found, NULL otherwise
   */
  const DcmRoleSelectionList *getRoleSelectionList(const char *key) const;

private:
  /// private undefined copy constructor
  DcmRoleSelectionMap(const DcmRoleSelectionMap& arg);

  /// private undefined copy assignment operator
  DcmRoleSelectionMap& operator=(const DcmRoleSelectionMap& arg);

  /// map of role selection lists
  DcmSimpleMap<DcmRoleSelectionList *> map_;

};

#endif