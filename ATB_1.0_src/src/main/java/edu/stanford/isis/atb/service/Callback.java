/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/



package edu.stanford.isis.atb.service;


/**
 * @author Vitaliy Semeshko
 */
public interface Callback<T> {

	public void onSuccess(T result);
	
	public void onFailure(Throwable caught);
	
}