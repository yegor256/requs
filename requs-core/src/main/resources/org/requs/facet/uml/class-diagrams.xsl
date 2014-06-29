<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:re="http://www.requs.org"
    xmlns:r="org.requs.facet.uml.Plant" version="2.0"
    exclude-result-prefixes="xs r re">
    <xsl:import href="uml/functions.xsl"/>
    <xsl:output method="xml" cdata-section-elements="svg html"/>
    <xsl:strip-space elements="*" />
    <xsl:template match="spec/types/type">
        <xsl:copy>
            <xsl:apply-templates select="(node() except diagrams)|@*"/>
            <xsl:variable name="uml">
                <xsl:text>@startuml&#10;</xsl:text>
                <xsl:text>title </xsl:text>
                <xsl:value-of select="name"/>
                <xsl:text>: Class Diagram&#10;</xsl:text>
                <xsl:apply-templates select="." mode="uml"/>
                <xsl:text>&#10;@enduml</xsl:text>
            </xsl:variable>
            <diagrams>
                <xsl:apply-templates select="diagrams/*"/>
                <diagram>
                    <uml><xsl:value-of select="$uml"/></uml>
                    <svg><xsl:value-of select="r:svg($uml)"/></svg>
                </diagram>
            </diagrams>
        </xsl:copy>
    </xsl:template>
    <xsl:template match="type" mode="uml">
        <xsl:variable name="type" select="name"/>
        <xsl:text>class </xsl:text>
        <xsl:value-of select="$type"/>
        <xsl:text> {&#10;</xsl:text>
        <xsl:for-each select="slots/slot[not(type)]">
            <xsl:text>  </xsl:text>
            <xsl:value-of select="name"/>
            <xsl:if test="arity = 'ANY' or arity = 'MANY'">
                <xsl:text>[]</xsl:text>
            </xsl:if>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
        <xsl:text>}&#10;</xsl:text>
        <xsl:for-each select="slots/slot[type]">
            <xsl:text>class </xsl:text>
            <xsl:value-of select="type"/>
            <xsl:text>&#10;</xsl:text>
            <xsl:value-of select="$type"/>
            <xsl:text> o-- </xsl:text>
            <xsl:value-of select="type"/>
            <xsl:text>: </xsl:text>
            <xsl:value-of select="name"/>
            <xsl:text>&#10;</xsl:text>
        </xsl:for-each>
    </xsl:template>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>
</xsl:stylesheet>
