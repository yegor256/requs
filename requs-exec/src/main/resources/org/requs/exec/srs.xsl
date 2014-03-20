<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns="http://www.w3.org/1999/xhtml" version="2.0" exclude-result-prefixes="xs">
    <xsl:template match="/">
        <xsl:text disable-output-escaping="yes">&lt;!DOCTYPE html&gt;</xsl:text>
        <xsl:apply-templates select="spec"/>
    </xsl:template>
    <xsl:template match="spec">
        <html lang="en">
            <head>
                <meta charset="UTF-8"/>
                <meta name="description" content="SRS"/>
                <meta name="keywords" content="SRS, software requirements specification"/>
                <meta name="author" content="requs"/>
                <link href="//netdna.bootstrapcdn.com/bootstrap/3.1.1/css/bootstrap.min.css" rel="stylesheet"/>
                <link href="//netdna.bootstrapcdn.com/font-awesome/4.0.3/css/font-awesome.css" rel="stylesheet"/>
                <meta name="viewport" content="width=device-width, initial-scale=1.0" />
            </head>
            <body>
                <xsl:apply-templates select="types/type"/>
            </body>
        </html>
    </xsl:template>
    <xsl:template match="types/type">
        <div>
            <xsl:value-of select="name"/>
            <xsl:text> is a </xsl:text>
            <xsl:apply-templates select="methods/method"/>
        </div>
    </xsl:template>
    <xsl:template match="methods/method">
        <div>
            <div>
                <xsl:value-of select="id"/>
                <xsl:text> where </xsl:text>
                <xsl:text>the </xsl:text>
                <xsl:value-of select="object"/>
                <xsl:text> </xsl:text>
                <xsl:value-of select="signature"/>
                <xsl:text> the </xsl:text>
                <xsl:value-of select="result"/>
                <xsl:text>:</xsl:text>
            </div>
            <xsl:apply-templates select="steps/step"/>
        </div>
    </xsl:template>
</xsl:stylesheet>
