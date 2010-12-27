/**
 * RQDQL.com
 *
 * This source file is subject to the new BSD license that is bundled
 * with this package in the file LICENSE.txt. It is also available
 * through the world-wide-web at this URL: http://www.rqdql.com/LICENSE.txt
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@rqdql.com so we can send you a copy immediately.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * @author Yegor Bugayenko <egor@rqdql.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

/**
 * Globally-defined object that you can use in order to convert
 * any text to RQDQL XML report, and in order to render the report
 * received and use certain properties of it.
 */
var rqdql = {};

/**
 * Convert any text to RQDQL object, that can be used later
 *
 * Should be used like this:
 * <code>
 * rqdql.parse(
 *   'User is a "human being"', // text to parse
 *   function(scope) { // function to be called when the RQDQL scope object is ready
 *     if (!scope.isValid()) {
 *       alert('the text is not valid');
 *     }
 *   }
 * );
 * </code>
 *
 * @param string Text to validate
 * @param function Callback to use when the scope document is ready
 * @return void
 */
rqdql.parse = function(text, callback)
{
    // sanity check
    if (typeof jQuery == 'undefined') {
        throw new Error('jQuery is NOT loaded');
    }

    $.ajax(
        {
            url: "http://tracfacade.fazend.com/rqdql",
            data: { 'text': text },
            dataType: "jsonp",
            success: function(data)
            {
                var xml = (new DOMParser()).parseFromString(data, "text/xml");
                var scope = new rqdql.Scope(xml);
                callback(scope);
            },
            error: function(XMLHttpRequest, textStatus, errorThrown)
            {
                var xml = (new DOMParser()).parseFromString(
                    '<?xml version="1.0"?><rqdql/>', 
                    "text/xml"
                );
                $('<fatal/>').text(textStatus).appendTo(xml);
                var scope = new rqdql.Scope(xml);
                callback(scope);
            }
        }
    );
};

/**
 * Constructor of Scope object
 */
rqdql.Scope = function(input)
{
    return {
        /**
         * RQDQL XML response
         */
        xml: $(input),
    
        /**
         * Convert the scope to the plain XML
         */
        toString: function()
        {
            return (new XMLSerializer()).serializeToString(input);
        },
        
        /**
         * The scope is valid, and was processed properly
         */
        isValid: function()
        {
            if (this.xml.children().find('fatal').length) {
                return false;
            }
            if (this.xml.find('errorsCount').text() > 0) {
                return false;
            }
            return true;
        },
        
        /**
         * Get version of RQDQL parser
         */
        getRqdqlVersion: function()
        {
            if (!this.xml.find('metrics version').length) {
                return 'unknown';
            }
            return this.xml.find('metrics version').text();
        },
        
        /**
         * Get ambiguity, as float number
         */
        getAmbiguity: function()
        {
            if (!this.xml.find('metrics ambiguity').length) {
                return '?';
            }
            return parseFloat(this.xml.find('metrics ambiguity').text());
        },
        
        /**
         * Get total number of errors
         */
        getErrorsCount: function()
        {
            if (!this.xml.find('metrics errorsCount').length) {
                return '?';
            }
            return parseInt(this.xml.find('metrics errorsCount').text());
        },
        
        /**
         * Get full list of errors for the given line
         */
        getErrorsByLine: function(line)
        {
            var result = new Array();
            this.xml.find('errors error[line=' + line + ']').each(
                function(index, element) 
                {
                    result[index] = $(element).text();
                }
            );
            return result;
        },
        
        /**
         * Get full list of objects found at this line
         */
        getObjectsByLine: function(line)
        {
            var result = new Array();
            this.xml.find('links loc:has(line:contains(' + line + '))').each(
                function(index, element) 
                {
                    result[index] = $(element).attr('name').toString();
                }
            );
            return result;
        },
        
    };
};
