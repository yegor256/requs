<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="mentioned/where">
        <xsl:copy>
            <xsl:variable name="line" select="."/>
            <xsl:variable name="file" select="/spec/files/file[@line &lt;= $line and not(following-sibling::file/@line &lt; $line)]"/>
            <xsl:value-of select="$file/@id"/>
            <xsl:text>:</xsl:text>
            <xsl:value-of select="$line - $file/@line"/>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
