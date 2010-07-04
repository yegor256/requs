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
 * @version $Id$
 */

/**
 * Render the content received from RQDQL
 */
function render()
{
    // we already rendered it
    if ((render.rendered != undefined) && render.rendered == this.value) {
        return;
    }
    // save it for the future, to avoid double renderings
    render.rendered = this.value;

    rqdql.parse(
        render.rendered,
        function(scope)
        {
            $("#xml").text(scope.toString());
            $('#status')
                .empty()
                .append('<span/>')
                    .find(':last')
                    .html(scope.isValid() ? '&#x2714;' : '&#x2718;')
                    .css('font-size', '3em')
                    .css('color', scope.isValid() ? 'green' : 'red')
                    .parent()
                .append('<br/>')
                .append('<span/>')
                    .find(':last')
                    .text('RQDQL version:')
                    .addClass('header')
                    .parent()
                .append('<span/>')
                    .find(':last')
                    .text(scope.getRqdqlVersion())
                    .parent()
                .append('<br/>')
                .append('<span/>')
                    .find(':last')
                    .text('Ambiguity:')
                    .addClass('header')
                    .parent()
                .append('<span/>')
                    .find(':last')
                    .text(scope.getAmbiguity())
                    .parent()
                .append('<br/>')
                .append('<span/>')
                    .find(':last')
                    .text('Errors total:')
                    .addClass('header')
                    .parent()
                .append('<span/>')
                    .find(':last')
                    .text(scope.getErrorsCount())
                    .parent();
        }
    );
};

/**
 * Run this method when the document is loaded
 */
$(document).ready(
    function()
    {
        $("#example").keyup(render);
    }
);
