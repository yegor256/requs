<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns="http://www.w3.org/1999/xhtml" version="2.0">
    <xsl:include href="_layout.xsl"/>
    <xsl:template name="head">
        <title>TBDs</title>
        <style type="text/css">
            .intro { font-size: 0.9em; color: #999; }
            .type { margin-top: 3em; }
            .slots { margin-left: 1em; margin-top: 1em; }
            .method { margin-top: 1em; margin-left: 1em; }
            .steps { margin-top: 1em; margin-left: 1em }
            .step { margin-top: 0.25em; }
            .nfrs { margin-top: 1em; margin-left: 1em }
            .nfr { margin-top: 0.25em; }
            .exception { margin-left: 1em; margin-top: 1em; margin-bottom: 1em; }
            .informal { color: #666; }
            .warning { color: #d9534f; }
            .crud { color: #5cb85c; }
            .label { margin-left: 0.5em; color: white; border-radius: .25em; font-size: 0.85em; padding: .1em .3em .15em; }
            .attribute { background-color: #999; }
            .sealed { background-color: #5cb85c; }
            .seal { background-color: #5bc0de; }
        </style>
    </xsl:template>
    <xsl:template name="body">
        <xsl:apply-templates select="/tbds"/>
    </xsl:template>
    <xsl:template match="tbds">
        <h1><xsl:text>TBDs</xsl:text></h1>
        <table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Subject</th>
                    <th>Description</th>
                </tr>
            </thead>
            <tbody>
                <xsl:apply-templates select="tbd"/>
            </tbody>
        </table>
    </xsl:template>
    <xsl:template match="tbd">
        <tr>
            <td><xsl:value-of select="@id"/></td>
            <td><xsl:value-of select="subject"/></td>
            <td><xsl:value-of select="description"/></td>
        </tr>
    </xsl:template>
</xsl:stylesheet>
