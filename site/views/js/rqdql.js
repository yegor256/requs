/**
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: index.php 2236 2010-07-03 17:26:54Z yegor256@yahoo.com $
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
