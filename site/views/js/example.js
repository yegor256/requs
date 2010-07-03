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
    
    $.ajax(
        {
            'url': "http://tracfacade.fazend.com/rqdql",
            'data': { 'text': this.value },
            'dataType': 'jsonp',
            'success': function(data)
            {
                var xml = (new DOMParser()).parseFromString(data, "text/xml");
                $("#xml").html(data.replace(/</g, '&lt;'));
            }
        }
    );
}

/**
 * Run this method when the document is loaded
 */
$(document).ready(
    function()
    {
        $("#example").keyup(render);
    }
);
