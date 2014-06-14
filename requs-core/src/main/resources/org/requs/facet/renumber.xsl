<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="2.0">
    <xsl:output method="xml"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="mentioned/where">
        <xsl:copy>
            <xsl:call-template name="line-number">
                <xsl:with-param name="line" select="number(.)"/>
            </xsl:call-template>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="error/@line">
        <xsl:attribute name="{name()}">
            <xsl:call-template name="line-number">
                <xsl:with-param name="line" select="number(.)"/>
            </xsl:call-template>
        </xsl:attribute>
    </xsl:template>
    <xsl:template name="line-number">
        <xsl:param name="line"/>
        <xsl:variable name="file" select="/spec/files/file[@line &lt;= $line and not(following-sibling::file/@line &lt;= $line)]"/>
        <xsl:value-of select="$file/@id"/>
        <xsl:text>:</xsl:text>
        <xsl:value-of select="$line - $file/@line + 1"/>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
